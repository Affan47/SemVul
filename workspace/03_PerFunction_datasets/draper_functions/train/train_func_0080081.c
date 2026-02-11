CityHash128(const char *s, size_t len) {
  uint128 r;
  if (len >= 16) {
    r.first = (uint64) (Fetch64(s) ^ k3);
    r.second = (uint64) (Fetch64(s + 8));

    return CityHash128WithSeed(s + 16,
                               len - 16,
                               r);

  } else if (len >= 8) {
    r.first = (uint64) (Fetch64(s) ^ (len * k0));
    r.second = (uint64) (Fetch64(s + len - 8) ^ k1);

    return CityHash128WithSeed(NULL,
                               0,
                               r);
  } else {
    r.first = (uint64) k0;
    r.second = (uint64) k1;
    return CityHash128WithSeed(s, len, r);
  }
}
