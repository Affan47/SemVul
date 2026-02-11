TrueMotion(uint8_t *dst, int size) {
  const uint8_t* top = dst - BPS;
  const uint8_t* const clip0 = clip1 + 255 - top[-1];
  int y;
  for (y = 0; y < size; ++y) {
    const uint8_t* const clip = clip0 + dst[-1];
    int x;
    for (x = 0; x < size; ++x) {
      dst[x] = clip[top[x]];
    }
    dst += BPS;
  }
}
