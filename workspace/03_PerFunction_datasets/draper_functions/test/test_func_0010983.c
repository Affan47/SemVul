matrixt_by_vector4(numeric_t mat[4][MAXCODES], numeric_t vec[4], numeric_t out[4]) {
#ifdef USE_SSE3

  __m128 o = _mm_setzero_ps();
  int j;

  for (j = 0; j < 4; j++) {
    __m128 m = _mm_load_ps(&mat[j][0]);
    __m128 vj = _mm_load1_ps(&vec[j]);
    o = _mm_add_ps(o, _mm_mul_ps(vj,m));
  }
  _mm_store_ps(out, o);
#else
  int j,k;
  for (j = 0; j < 4; j++) {
    double sum = 0;
    for (k = 0; k < 4; k++)
      sum += vec[k] * mat[k][j];
    out[j] = sum;
  }
#endif
}
