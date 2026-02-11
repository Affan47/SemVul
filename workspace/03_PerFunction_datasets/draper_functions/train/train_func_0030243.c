ResumeProfilerEx(int flags, int tag) {
#ifdef ENABLE_LOGGING_AND_PROFILING
  if (flags & PROFILER_MODULE_HEAP_SNAPSHOT) {


    i::Heap::CollectAllGarbage(false);

    flags &= ~(PROFILER_MODULE_HEAP_SNAPSHOT | PROFILER_MODULE_CPU);
    const int current_flags = i::Logger::GetActiveProfilerModules();
    i::Logger::ResumeProfiler(flags, tag);
    i::Heap::CollectAllGarbage(false);
    i::Logger::PauseProfiler(~current_flags & flags, tag);
  } else {
    i::Logger::ResumeProfiler(flags, tag);
  }
#endif
}
