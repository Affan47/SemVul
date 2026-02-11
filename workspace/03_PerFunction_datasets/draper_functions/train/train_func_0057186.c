RunAllTests() {

  if (!GTestIsInitialized()) {
    printf("%s",
           "\nThis test program did NOT call ::testing::InitGoogleTest "
           "before calling RUN_ALL_TESTS().  Please fix it.\n");
    return 1;
  }


  if (g_help_flag)
    return 0;


  PostFlagParsingInit();


  internal::WriteToShardStatusFileIfNeeded();


  bool in_subprocess_for_death_test = false;

#if GTEST_HAS_DEATH_TEST
  in_subprocess_for_death_test = (internal_run_death_test_flag_.get() != NULL);
#endif

  const bool should_shard = ShouldShard(kTestTotalShards, kTestShardIndex,
                                        in_subprocess_for_death_test);


  const bool has_tests_to_run = FilterTests(should_shard
                                              ? HONOR_SHARDING_PROTOCOL
                                              : IGNORE_SHARDING_PROTOCOL) > 0;


  if (GTEST_FLAG(list_tests)) {

    ListTestsMatchingFilter();
    return 0;
  }

  random_seed_ = GTEST_FLAG(shuffle) ?
      GetRandomSeedFromFlag(GTEST_FLAG(random_seed)) : 0;


  bool failed = false;

  TestEventListener* repeater = listeners()->repeater();

  repeater->OnTestProgramStart(*parent_);


  const int repeat = in_subprocess_for_death_test ? 1 : GTEST_FLAG(repeat);

  const bool forever = repeat < 0;
  for (int i = 0; forever || i != repeat; i++) {
    ClearResult();

    const TimeInMillis start = GetTimeInMillis();


    if (has_tests_to_run && GTEST_FLAG(shuffle)) {
      random()->Reseed(random_seed_);


      ShuffleTests();
    }


    repeater->OnTestIterationStart(*parent_, i);


    if (has_tests_to_run) {

      repeater->OnEnvironmentsSetUpStart(*parent_);
      ForEach(environments_, SetUpEnvironment);
      repeater->OnEnvironmentsSetUpEnd(*parent_);


      if (!Test::HasFatalFailure()) {
        for (int test_index = 0; test_index < total_test_case_count();
             test_index++) {
          GetMutableTestCase(test_index)->Run();
        }
      }


      repeater->OnEnvironmentsTearDownStart(*parent_);
      std::for_each(environments_.rbegin(), environments_.rend(),
                    TearDownEnvironment);
      repeater->OnEnvironmentsTearDownEnd(*parent_);
    }

    elapsed_time_ = GetTimeInMillis() - start;


    repeater->OnTestIterationEnd(*parent_, i);


    if (!Passed()) {
      failed = true;
    }


    UnshuffleTests();

    if (GTEST_FLAG(shuffle)) {

      random_seed_ = GetNextRandomSeed(random_seed_);
    }
  }

  repeater->OnTestProgramEnd(*parent_);


  return failed ? 1 : 0;
}
