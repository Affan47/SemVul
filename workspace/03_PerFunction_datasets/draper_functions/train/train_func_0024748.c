get_stacktrace_addresses(int impl_stacktrace_depth)
{
  const int STACKTRACE_ARRAY_SIZE = 100;
  void *stacktrace_array[STACKTRACE_ARRAY_SIZE];
  const size_t stacktrace_size = backtrace(stacktrace_array,
    STACKTRACE_ARRAY_SIZE);
  return rcp(new StacktraceAddresses(stacktrace_array, stacktrace_size,
      impl_stacktrace_depth+1));
}
