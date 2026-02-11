parse_uint_radix(const char* str,
                               int n,
                               void* dest,
                               int radix) {
  unsigned long r;
  if (!parse_ulong_radix(str, n, &r, radix)) return false;
  if ((uint)r != r) return false;
  if (dest == NULL) return true;
  *(reinterpret_cast<unsigned int*>(dest)) = r;
  return true;
}
