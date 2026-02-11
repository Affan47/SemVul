ExecDeathTestFork(char* const* argv, int close_fd) {
  ExecDeathTestArgs args = { argv, close_fd };
  pid_t child_pid = -1;

#  if GTEST_HAS_CLONE
  const bool use_fork = GTEST_FLAG(death_test_use_fork);

  if (!use_fork) {
    static const bool stack_grows_down = StackGrowsDown();
    const size_t stack_size = getpagesize();

    void* const stack = mmap(NULL, stack_size, PROT_READ | PROT_WRITE,
                             MAP_ANON | MAP_PRIVATE, -1, 0);
    GTEST_DEATH_TEST_CHECK_(stack != MAP_FAILED);
    void* const stack_top =
        static_cast<char*>(stack) + (stack_grows_down ? stack_size : 0);

    child_pid = clone(&ExecDeathTestChildMain, stack_top, SIGCHLD, &args);

    GTEST_DEATH_TEST_CHECK_(munmap(stack, stack_size) != -1);
  }
#  else
  const bool use_fork = true;
#  endif

  if (use_fork && (child_pid = fork()) == 0) {
      ExecDeathTestChildMain(&args);
      _exit(0);
  }

  GTEST_DEATH_TEST_CHECK_(child_pid != -1);
  return child_pid;
}
