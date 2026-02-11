CityMurmur(const char *s, size_t len, uint128_t seed) {
  uint64_t a = Uint128Low64(seed);
  uint64_t b = Uint128High64(seed);
  uint64_t c = 0;
  uint64_t d = 0;
  signed long l = len - 16;
  if (l <= 0) {
    a = ShiftMix(a * k1) * k1;
    c = b * k1 + HashLen0to16(s, len);
    d = ShiftMix(a + (len >= 8 ? Fetch(s) : c));
  } else {
    c = HashLen16(Fetch(s + len - 8) + k1, a);
    d = HashLen16(b + len, c + Fetch(s + len - 16));
    a += d;
    do {
      a ^= ShiftMix(Fetch(s) * k1) * k1;
      a *= k1;
      b ^= a;
      c ^= ShiftMix(Fetch(s + 8) * k1) * k1;
      c *= k1;
      d ^= c;
      s += 16;
      l -= 16;
    } while (l > 0);
  }
  a = HashLen16(a, c);
  b = HashLen16(d, b);
  return uint128_t(a ^ b, HashLen16(b, a));
}
