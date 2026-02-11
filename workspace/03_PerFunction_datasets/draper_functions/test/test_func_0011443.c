PackARGB(const uint8_t* a, const uint8_t* r, const uint8_t* g,
                     const uint8_t* b, int len, uint32_t* out) {
  int i;
  for (i = 0; i < len; ++i) {
    out[i] = MakeARGB32(a[4 * i], r[4 * i], g[4 * i], b[4 * i]);
  }
}
