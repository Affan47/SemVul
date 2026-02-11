operator==(const StringPiece& x, const StringPiece& y) {
  int32_t len = x.size();
  if (len != y.size()) {
    return false;
  }
  if (len == 0) {
    return true;
  }
  const char* p = x.data();
  const char* p2 = y.data();

  --len;
  if (p[len] != p2[len]) return false;

  return uprv_memcmp(p, p2, len) == 0;
}
