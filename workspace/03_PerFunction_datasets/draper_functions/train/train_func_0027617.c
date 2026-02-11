Run() {
  if (!HasSameFixtureClass()) return;

  internal::UnitTestImpl* const impl = internal::GetUnitTestImpl();
#if GTEST_HAS_SEH

  impl->os_stack_trace_getter()->UponLeavingGTest();
  __try {
    SetUp();
  } __except(internal::UnitTestOptions::GTestShouldProcessSEH(
      GetExceptionCode())) {
    AddExceptionThrownFailure(GetExceptionCode(), "SetUp()");
  }


  if (!HasFatalFailure()) {
    impl->os_stack_trace_getter()->UponLeavingGTest();
    __try {
      TestBody();
    } __except(internal::UnitTestOptions::GTestShouldProcessSEH(
        GetExceptionCode())) {
      AddExceptionThrownFailure(GetExceptionCode(), "the test body");
    }
  }


  impl->os_stack_trace_getter()->UponLeavingGTest();
  __try {
    TearDown();
  } __except(internal::UnitTestOptions::GTestShouldProcessSEH(
      GetExceptionCode())) {
    AddExceptionThrownFailure(GetExceptionCode(), "TearDown()");
  }

#else
  impl->os_stack_trace_getter()->UponLeavingGTest();
  SetUp();


  if (!HasFatalFailure()) {
    impl->os_stack_trace_getter()->UponLeavingGTest();
    TestBody();
  }


  impl->os_stack_trace_getter()->UponLeavingGTest();
  TearDown();
#endif
}
