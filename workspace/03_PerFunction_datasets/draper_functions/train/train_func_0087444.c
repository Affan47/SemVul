VerifyRegistration(const int& tick_counter) {

    EXPECT_GT(GetCallbackCount(), 0);

    EXPECT_EQ(FLAGS_test_profiler_enabled, IsTimerEnabled());

    if (FLAGS_test_profiler_signal_handler) {
      EXPECT_EQ(FLAGS_test_profiler_enabled, IsSignalEnabled());
    }
    uint64 interrupts_before = GetInterruptCount();

    int old_tick_count = tick_counter;
    Delay(kSleepInterval);
    int new_tick_count = tick_counter;
    uint64 interrupts_after = GetInterruptCount();
    if (FLAGS_test_profiler_enabled) {
      EXPECT_GT(new_tick_count, old_tick_count);
      EXPECT_GT(interrupts_after, interrupts_before);
    } else {
      EXPECT_EQ(new_tick_count, old_tick_count);
      EXPECT_EQ(interrupts_after, interrupts_before);
    }
  }
