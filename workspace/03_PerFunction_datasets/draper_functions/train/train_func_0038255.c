select_e(ESL_RANDOMNESS *rng, const P7_OPROFILE *om, const P7_OMX *ox, int i, int *ret_k)
{
  int    Q     = p7O_NQF(ox->M);
  double sum   = 0.0;
  double roll  = esl_random(rng);
  double norm  = 1.0 / ox->xmx[i*p7X_NXCELLS+p7X_E];
  __m128 xEv   = _mm_set1_ps(norm);
  union { __m128 v; float p[4]; } u;
  int    q,r;

  while (1) {
    for (q = 0; q < Q; q++)
      {
	u.v = _mm_mul_ps(ox->dpf[i][q*3 + p7X_M], xEv);
	for (r = 0; r < 4; r++) {
	  sum += u.p[r];
	  if (roll < sum) { *ret_k = r*Q + q + 1; return p7T_M;}
	}

	u.v = _mm_mul_ps(ox->dpf[i][q*3 + p7X_D], xEv);
	for (r = 0; r < 4; r++) {
	  sum += u.p[r];
	  if (roll < sum) { *ret_k = r*Q + q + 1; return p7T_D;}
	}
      }
    ESL_DASSERT1((sum > 0.99));
  }

  ESL_EXCEPTION(-1, "unreached code was reached. universe collapses.");
}
