__gmp_mt_recalc_buffer (gmp_uint_least32_t mt[])
{
  gmp_uint_least32_t y;
  int kk;

  for (kk = 0; kk < N - M; kk++)
    {
      y = (mt[kk] & 0x80000000) | (mt[kk + 1] & 0x7FFFFFFF);
      mt[kk] = mt[kk + M] ^ (y >> 1) ^ ((y & 0x01) != 0 ? MATRIX_A : 0);
    }
  for (; kk < N - 1; kk++)
    {
      y = (mt[kk] & 0x80000000) | (mt[kk + 1] & 0x7FFFFFFF);
      mt[kk] = mt[kk - (N - M)] ^ (y >> 1) ^ ((y & 0x01) != 0 ? MATRIX_A : 0);
    }

  y = (mt[N - 1] & 0x80000000) | (mt[0] & 0x7FFFFFFF);
  mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x01) != 0 ? MATRIX_A : 0);
}
