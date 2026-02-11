Hash32WithSeed(const char *s, size_t len, uint32_t seed) {
  if (len <= 24) {
    if (len >= 13) return Hash32Len13to24(s, len, seed * c1);
    else if (len >= 5) return Hash32Len5to12(s, len, seed);
    else return Hash32Len0to4(s, len, seed);
  }
  uint32_t h = Hash32Len13to24(s, 24, seed ^ len);
  return Mur(Hash32(s + 24, len - 24) + seed, h);
}
