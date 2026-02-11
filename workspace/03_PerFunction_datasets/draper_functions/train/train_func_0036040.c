MakeGeopotHeight(double *geop, double* gt, double *gq, double *ph, int nhor, int nlev)
{
  int i, j;
  double vtmp;
  double zrg;
  double z2log2;
  double *geopl, *gtl, *gql, *phl;

  z2log2 = 2.0 * log(2.0);
  vtmp   = (C_RV / RD) - 1.0;
  zrg    = 1.0 / Grav;

  if ( gq )
    {
      for ( j = nlev ; j > 1 ; j-- )
        {
          geopl = geop + nhor*(j-1);
          gtl   = gt   + nhor*(j-1);
          gql   = gq   + nhor*(j-1);
          phl   = ph   + nhor*(j-1);
#if defined(SX)
#pragma vdir nodep
#endif
#if defined(_OPENMP)
#pragma omp parallel for
#endif
          for ( i = 0; i < nhor; i++ )
            geopl[i] = geopl[i+nhor] + RD * gtl[i] * (1.0 + vtmp * gql[i])
                     * log(phl[i+nhor] / phl[i]);
        }

#if defined(SX)
#pragma vdir nodep
#endif
#if defined(_OPENMP)
#pragma omp parallel for
#endif
      for ( i = 0; i < nhor; i++ )
        geop[i] = geop[i+nhor] + RD * gt[i] * (1.0 + vtmp * gq[i]) * z2log2;
    }
  else
    {
      for ( j = nlev ; j > 1 ; j-- )
#if defined(SX)
#pragma vdir nodep
#endif
        for ( i = nhor * (j-1) ; i < nhor * j ; i++ )
          geop[i] = geop[i+nhor] + RD * gt[i] * log(ph[i+nhor] / ph[i]);

#if defined(SX)
#pragma vdir nodep
#endif
      for ( i = 0; i < nhor; i++ )
        geop[i] = geop[i+nhor] + RD * gt[i] * z2log2;
    }

#if defined(SX)
#pragma vdir nodep
#endif
#if defined(_OPENMP)
#pragma omp parallel for
#endif
  for ( i = 0; i < nhor * (nlev+1); i++ ) geop[i] *= zrg;
}
