gf_w4_bytwo_b_sse_region_2_xor(gf_region_data *rd, struct gf_bytwo_data *btd)
{
  uint8_t *d8, *s8;
  __m128i pp, m1, t1, t2, va, vb;

  s8 = (uint8_t *) rd->s_start;
  d8 = (uint8_t *) rd->d_start;

  pp = _mm_set1_epi8(btd->prim_poly&0xff);
  m1 = _mm_set1_epi8((btd->mask1)&0xff);

  while (d8 < (uint8_t *) rd->d_top) {
    va = _mm_load_si128 ((__m128i *)(s8));
    SSE_AB2(pp, m1, va, t1, t2);
    vb = _mm_load_si128 ((__m128i *)(d8));
    vb = _mm_xor_si128(vb, va);
    _mm_store_si128((__m128i *)d8, vb);
    d8 += 16;
    s8 += 16;
  }
}
