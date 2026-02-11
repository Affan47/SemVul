DC4(uint8_t *dst) {
  uint32_t dc = 4;
  int i;
  for (i = 0; i < 4; ++i) dc += dst[i - BPS] + dst[-1 + i * BPS];
  dc >>= 3;
  for (i = 0; i < 4; ++i) memset(dst + i * BPS, dc, 4);
}
