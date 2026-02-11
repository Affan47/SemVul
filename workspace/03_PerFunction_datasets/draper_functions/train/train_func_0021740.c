ApplyAlphaMultiply4444(uint8_t* rgba4444,
                                               int w, int h, int stride,
                                               int rg_byte_pos ) {
  while (h-- > 0) {
    int i;
    for (i = 0; i < w; ++i) {
      const uint32_t rg = rgba4444[2 * i + rg_byte_pos];
      const uint32_t ba = rgba4444[2 * i + (rg_byte_pos ^ 1)];
      const uint8_t a = ba & 0x0f;
      const uint32_t mult = MULTIPLIER(a);
      const uint8_t r = multiply(dither_hi(rg), mult);
      const uint8_t g = multiply(dither_lo(rg), mult);
      const uint8_t b = multiply(dither_hi(ba), mult);
      rgba4444[2 * i + rg_byte_pos] = (r & 0xf0) | ((g >> 4) & 0x0f);
      rgba4444[2 * i + (rg_byte_pos ^ 1)] = (b & 0xf0) | a;
    }
    rgba4444 += stride;
  }
}
