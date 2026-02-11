StreqExcept(const char* a, const char* b, const char* except) {
  const char* pa = a, *pb = b;
  const size_t exceptlen = strlen(except);
  while (1) {

    while (memchr(except, *pa, exceptlen))  pa++;
    while (memchr(except, *pb, exceptlen))  pb++;
    if ((*pa == '\0') && (*pb == '\0'))
      return true;
    if (*pa++ != *pb++)
      return false;
  }
}
