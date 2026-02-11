genind(int *nx, const double * restrict plev, const double * restrict fullp, long ngp, long nplev, long nhlev)
{
  long  i, lp, lh;
  int *nxl;
  double pres;

  memset(nx, 0, ngp*nplev*sizeof(int));

#if defined(_OPENMP)
#pragma omp parallel for default(shared) private(i, lh, pres, nxl)
#endif
  for ( lp = 0; lp < nplev; lp++ )
    {
      pres = plev[lp];
      nxl  = nx + lp*ngp;
      for ( lh = 0; lh < nhlev; lh++ )
	for ( i = 0; i < ngp ; i++ )
	   {
	     if ( pres > fullp[lh*ngp+i] ) nxl[i] = lh;
	   }
    }

}
