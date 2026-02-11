RunHeapBusyThreads() {
  KeyInit();
  if (!FLAGS_interfering_threads || FLAGS_no_threads)  return;

  const int n = 17;

  pthread_t tid;
  pthread_attr_t attr;
  CHECK_EQ(pthread_attr_init(&attr), 0);

  for (int i = 0; i < n; ++i) {
    VLOG(0) << "Creating extra thread " << i + 1;
    CHECK(pthread_create(&tid, &attr, HeapBusyThreadBody,
                         reinterpret_cast<void*>(i)) == 0);
  }

  Pause();
  Pause();
}
