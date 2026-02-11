pdeian (float *a, float *u, float *f, float *g, float *u0,
	       float *alpha, float *rho11, float *rho12, float *rho21, float *rho22,
	       float *u1, float *u2, float *beta, int factorize)
  {
    long i, nsl = ns;
    int j, mekj, k, nquad = __quadra ? 3 * nt : ns;
    if (factorize)
      pdemat (a, alpha, rho11, rho12, rho21, rho22, u1, u2, beta);
    rhsPDE (u, f, g);
    for (i = 0; i < nquad; i++)
      if (norme2 (u0[i]) != 0)
	{
	  if (__quadra)
	    {
	      k = i / 3;
	      j = i - 3 * k;
	      mekj = me[k][j];
	    }
	  else
	    mekj = i;
	  u[mekj] += u0[i] * penal;
	  if (factorize)
	    a[nsl * bdth + mekj] += id (u0[i]) * penal;
	}
    return gaussband (a, u, nsl, bdth, factorize, 1.F / penal);
  }
}
