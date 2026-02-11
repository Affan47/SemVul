main(int argc, char** argv) {

  static const int kAllocSize = kMaxSize + kPageSize;

  static const int kTotalAlloc = 400 << 20;
  static const int kAllocIterations = kTotalAlloc / kAllocSize;


  vector<char*> saved(kAllocIterations);
  for (int i = 0; i < kAllocIterations; i++) {
    saved[i] = new char[kAllocSize];
  }


  size_t slack_before;
  MallocExtension::instance()->GetNumericProperty("tcmalloc.slack_bytes",
                                                  &slack_before);


  size_t free_bytes = 0;
  for (int i = 0; i < saved.size(); i += 2) {
    delete[] saved[i];
    free_bytes += kAllocSize;
  }


  size_t slack_after;
  MallocExtension::instance()->GetNumericProperty("tcmalloc.slack_bytes",
                                                  &slack_after);
  CHECK_GE(slack_after, slack_before);
  size_t slack = slack_after - slack_before;

  CHECK_GT(double(slack), 0.9*free_bytes);
  CHECK_LT(double(slack), 1.1*free_bytes);


  static const int kBufSize = 1<<20;
  char* buffer = new char[kBufSize];
  MallocExtension::instance()->GetStats(buffer, kBufSize);
  VLOG(1, "%s", buffer);
  delete[] buffer;


  for (int i = 0; i < 5; i++) {
    static const int kIterations = 100000;
#ifdef HAVE_SYS_RESOURCE_H
    struct rusage r;
    getrusage(RUSAGE_SELF, &r);
    struct timeval tv_start = r.ru_utime;
#elif defined(_WIN32)
    long long int tv_start = GetTickCount();
#else
# error No way to calculate time on your system
#endif

    for (int i = 0; i < kIterations; i++) {
      size_t s;
      MallocExtension::instance()->GetNumericProperty("tcmalloc.slack_bytes",
                                                      &s);
    }

#ifdef HAVE_SYS_RESOURCE_H
    getrusage(RUSAGE_SELF, &r);
    struct timeval tv_end = r.ru_utime;
    int64 sumsec = static_cast<int64>(tv_end.tv_sec) - tv_start.tv_sec;
    int64 sumusec = static_cast<int64>(tv_end.tv_usec) - tv_start.tv_usec;
#elif defined(_WIN32)
    long long int tv_end = GetTickCount();
    int64 sumsec = (tv_end - tv_start) / 1000;

    int64 sumusec = ((tv_end - tv_start) % 1000) * 1000;
#else
# error No way to calculate time on your system
#endif
    fprintf(stderr, "getproperty: %6.1f ns/call\n",
            (sumsec * 1e9 + sumusec * 1e3) / kIterations);
  }

  printf("PASS\n");
  return 0;
}
