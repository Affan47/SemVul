WebPMultRowC(uint8_t* const ptr, const uint8_t* const alpha,
                  int width, int inverse) {
  int x;
  for (x = 0; x < width; ++x) {
    const uint32_t a = alpha[x];
    if (a != 255) {
      if (a == 0) {
        ptr[x] = 0;
      } else {
        const uint32_t scale = GetScale(a, inverse);
        ptr[x] = Mult(ptr[x], scale);
      }
    }
  }
}
