TearDown() {
  Isolate* isolate = Isolate::Current();
  if (isolate->cpu_profiler() != NULL) {
    delete isolate->cpu_profiler();
  }
  isolate->set_cpu_profiler(NULL);
}
