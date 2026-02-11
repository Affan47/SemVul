CityHash128(const char *s, size_t len) {
  return len >= 16 ?
      CityHash128WithSeed(s + 16, len - 16,
                          uint128_t(Fetch(s), Fetch(s + 8) + k0)) :
      CityHash128WithSeed(s, len, uint128_t(k0, k1));
}
