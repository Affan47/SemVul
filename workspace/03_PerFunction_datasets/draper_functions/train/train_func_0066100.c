VerifyUnregistration(const int& tick_counter) {

    int old_tick_count = tick_counter;
    Delay(kSleepInterval);
    int new_tick_count = tick_counter;
    EXPECT_EQ(old_tick_count, new_tick_count);

    if (GetCallbackCount() == 0) {
      if (FLAGS_test_profiler_signal_handler) {
        EXPECT_FALSE(IsSignalEnabled());
      }
      if (timer_separate_) {
        EXPECT_TRUE(IsTimerEnabled());
      } else {
        EXPECT_FALSE(IsTimerEnabled());
      }
    }
  }
