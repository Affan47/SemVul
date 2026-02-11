TestBasicRetryFailTest() {


  const size_t kHugeSize = (std::numeric_limits<size_t>::max)() / 2;
  void* p1 = malloc(kHugeSize);
  void* p2 = malloc(kHugeSize);
  CHECK(p2 == NULL);
  if (p1 != NULL) free(p1);

  char* q = new char[1024];
  CHECK(q != NULL);
  delete [] q;
}
