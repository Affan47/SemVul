GetActiveProfilerModules() {
  int result = PROFILER_MODULE_NONE;
  if (profiler_ != NULL && !profiler_->paused()) {
    result |= PROFILER_MODULE_CPU;
  }
  if (FLAG_log_gc) {
    result |= PROFILER_MODULE_HEAP_STATS | PROFILER_MODULE_JS_CONSTRUCTORS;
  }
  return result;
}
