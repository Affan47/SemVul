CityMurmur(const char *s, size_t len, uint128 seed) {
  uint64 a = Uint128Low64(seed);
  uint64 b = Uint128High64(seed);
  uint64 c = 0;
  uint64 d = 0;
  ssize_t l = len - 16;
  if (l <= 0) {
    a = ShiftMix(a * k1) * k1;
    c = b * k1 + HashLen0to16(s, len);
    d = ShiftMix(a + (len >= 8 ? Fetch64(s) : c));
  } else {
    c = HashLen16(Fetch64(s + len - 8) + k1, a);
    d = HashLen16(b + len, c + Fetch64(s + len - 16));
    a += d;
    do {
      a ^= ShiftMix(Fetch64(s) * k1) * k1;
      a *= k1;
      b ^= a;
      c ^= ShiftMix(Fetch64(s + 8) * k1) * k1;
      c *= k1;
      d ^= c;
      s += 16;
      l -= 16;
    } while (l > 0);
  }
  a = HashLen16(a, c);
  b = HashLen16(d, b);
  return uint128(a ^ b, HashLen16(b, a));
}
