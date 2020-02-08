#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include "gtest_ext.h"

using ::testing::HasSubstr;
using ::testing::AnyOf;
using ::testing::AllOf;
using ::testing::Not;

class ScheduleFile : public UnitTestFileManager
{
protected:
  ScheduleFile() : UnitTestFileManager("sched.txt") {}
};

typedef ScheduleFile ScheduleFileMultSchedules;

TEST_F(ScheduleFile, FileDoesntExist)
{
  std::string user_input = "nonexistent.txt";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("does not exist"), HasSubstr("doesn't exist")),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file doesn't exist.";
    // Ensure no other errors are show
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("end time"), HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, NoLocation)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("location"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "location. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT("main", user_input,
                    Not(AnyOf(HasSubstr("weekly schedule"), HasSubstr("symbol"),
                              HasSubstr("start time"), HasSubstr("end time"),
                              HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, NoWeeklySchedule)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("weekly schedule"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "weekly schedule. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT("main", user_input,
                    Not(AnyOf(HasSubstr("location"), HasSubstr("symbol"),
                              HasSubstr("start time"), HasSubstr("end time"),
                              HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, InvalidDay1)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nX";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("weekly schedule symbol"), HasSubstr("X"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the weekly schedule uses an "
           "invalid symbol. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("start time"),
                  HasSubstr("end time"), HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, InvalidDay2)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMWX";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("weekly schedule symbol"), HasSubstr("MWX"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the weekly schedule uses an "
           "invalid symbol. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("start time"),
                  HasSubstr("end time"), HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, NoStartTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n1124";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("start time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, NoStartTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\nabcd";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("start time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, NoEndTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n11:30\n1124";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("end time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain an "
           "end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, NoEndTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n8:35\nabcd";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("end time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain an "
           "end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, InvalidStartTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n25:30";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(HasSubstr("25:30"),
              AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("start time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "valid start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, InvalidStartTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n15:88";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT("main", user_input,
                    AllOf(HasSubstr("15:88"),
                          AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
                          HasSubstr("start time")))
        << "The program should show an error if the file does not contain a "
           "valid start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, InvalidEndTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n11:30\n100:25";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(HasSubstr("100:25"),
              AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("end time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "valid end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, InvalidEndTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n8:35\n12:999";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT("main", user_input,
                    AllOf(HasSubstr("12:999"),
                          AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
                          HasSubstr("end time")))
        << "The program should show an error if the file does not contain a "
           "valid end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFile, StartLaterThanEnd)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSCC 121\nE202\nMW\n18:35\n11:30\n";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(HasSubstr("18:35"), HasSubstr("11:30"),
              HasSubstr("happen before"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file contains a start time "
           "that happens after the end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"))))
        << "The program should not show other errors";
  })
}

// Test cases for schedule files with multiple schedules
TEST_F(ScheduleFileMultSchedules, NoLocation)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPSC 121\nE202\nMW\n11:30\n13:20\nCPSC 131";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("location"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "location. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT("main", user_input,
                    Not(AnyOf(HasSubstr("weekly schedule"), HasSubstr("symbol"),
                              HasSubstr("start time"), HasSubstr("end time"),
                              HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, NoWeeklySchedule)
{
  std::string user_input = "sched.txt";
  std::string file_contents = "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("weekly schedule"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "weekly schedule. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT("main", user_input,
                    Not(AnyOf(HasSubstr("location"), HasSubstr("symbol"),
                              HasSubstr("start time"), HasSubstr("end time"),
                              HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, InvalidDay1)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nX";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("weekly schedule symbol"), HasSubstr("X"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the weekly schedule uses an "
           "invalid symbol. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("start time"),
                  HasSubstr("end time"), HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, InvalidDay2)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMWX";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("weekly schedule symbol"), HasSubstr("MWX"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the weekly schedule uses an "
           "invalid symbol. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("start time"),
                  HasSubstr("end time"), HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, NoStartTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\n1124";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("start time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, NoStartTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\nabcd";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("start time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, NoEndTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\n11:30\n1124";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("end time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain an "
           "end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, NoEndTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\n8:35\nabcd";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(AnyOf(HasSubstr("Unable"), HasSubstr("unable")),
              HasSubstr("end time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain an "
           "end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, InvalidStartTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\n25:30";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();

  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(HasSubstr("25:30"),
              AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("start time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "valid start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, InvalidStartTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\n15:88";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT("main", user_input,
                    AllOf(HasSubstr("15:88"),
                          AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
                          HasSubstr("start time")))
        << "The program should show an error if the file does not contain a "
           "valid start time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("end time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, InvalidEndTime1)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\n11:30\n100:25";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(HasSubstr("100:25"),
              AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
              HasSubstr("end time"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file does not contain a "
           "valid end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, InvalidEndTime2)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSC 121\nE202\nMW\n8:35\n12:999";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT("main", user_input,
                    AllOf(HasSubstr("12:999"),
                          AnyOf(HasSubstr("Invalid"), HasSubstr("invalid")),
                          HasSubstr("end time")))
        << "The program should show an error if the file does not contain a "
           "valid end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"), HasSubstr("start time"),
                  HasSubstr("happen before"))))
        << "The program should not show other errors";
  })
}

TEST_F(ScheduleFileMultSchedules, StartLaterThanEnd)
{
  std::string user_input = "sched.txt";
  std::string file_contents =
      "CPS 131\nE101\nMW\n8:30\n11:20\nCPSCC 121\nE202\nMW\n18:35\n11:30\n";
  std::ofstream outfile("sched.txt");
  outfile << file_contents;
  outfile.close();
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECTHAT(
        "main", user_input,
        AllOf(HasSubstr("18:35"), HasSubstr("11:30"),
              HasSubstr("happen before"),
              AnyOf(HasSubstr("Invalid file"), HasSubstr("invalid file"))))
        << "The program should show an error if the file contains a start time "
           "that happens after the end time. File contents:\n"
        << file_contents;
    // Ensure no other errors are shown
    ASSERT_EXECTHAT(
        "main", user_input,
        Not(AnyOf(HasSubstr("location"), HasSubstr("weekly schedule"),
                  HasSubstr("symbol"))))
        << "The program should not show other errors";
  })
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  ::testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
