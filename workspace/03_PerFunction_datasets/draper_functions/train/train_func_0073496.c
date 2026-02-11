VP8YuvToBgra32(const uint8_t* y, const uint8_t* u, const uint8_t* v,
                    uint8_t* dst) {
  int n;
  for (n = 0; n < 32; n += 2) {
    const __m128i tmp0_1 = GetRGBA32b(y[n + 0], u[n + 0], v[n + 0]);
    const __m128i tmp0_2 = GetRGBA32b(y[n + 1], u[n + 1], v[n + 1]);
    const __m128i tmp1_1 = _mm_shuffle_epi32(tmp0_1, _MM_SHUFFLE(3, 0, 1, 2));
    const __m128i tmp1_2 = _mm_shuffle_epi32(tmp0_2, _MM_SHUFFLE(3, 0, 1, 2));
    const __m128i tmp2_1 = _mm_packs_epi32(tmp1_1, tmp1_2);
    const __m128i tmp3 = _mm_packus_epi16(tmp2_1, tmp2_1);
    _mm_storel_epi64((__m128i*)dst, tmp3);
    dst += 4 * 2;
  }
}
