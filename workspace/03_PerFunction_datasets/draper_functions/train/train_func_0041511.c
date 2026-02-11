parse_ulonglong_radix(const char* str,
                                    int n,
                                    void* dest,
                                    int radix) {
  if (n == 0) return false;
  char buf[kMaxNumberLength+1];
  str = TerminateNumber(buf, str, &n);
  if (str[0] == '-') {


    return false;
  }
  char* end;
  errno = 0;
  uint64 r = strtoull(str, &end, radix);
  if (end != str + n) return false;
  if (errno) return false;
  if (dest == NULL) return true;
  *(reinterpret_cast<uint64*>(dest)) = r;
  return true;
}
