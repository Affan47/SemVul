VP8YuvToRgba32(const uint8_t* y, const uint8_t* u, const uint8_t* v,
                    uint8_t* dst) {
  int n;
  for (n = 0; n < 32; n += 4) {
    const __m128i tmp0_1 = VP8GetRGBA32b(y[n + 0], u[n + 0], v[n + 0]);
    const __m128i tmp0_2 = VP8GetRGBA32b(y[n + 1], u[n + 1], v[n + 1]);
    const __m128i tmp0_3 = VP8GetRGBA32b(y[n + 2], u[n + 2], v[n + 2]);
    const __m128i tmp0_4 = VP8GetRGBA32b(y[n + 3], u[n + 3], v[n + 3]);
    const __m128i tmp1_1 = _mm_packs_epi32(tmp0_1, tmp0_2);
    const __m128i tmp1_2 = _mm_packs_epi32(tmp0_3, tmp0_4);
    const __m128i tmp2 = _mm_packus_epi16(tmp1_1, tmp1_2);
    _mm_storeu_si128((__m128i*)dst, tmp2);
    dst += 4 * 4;
  }
}
