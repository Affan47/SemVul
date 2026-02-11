check_lat_range(long nlats, double *lats)
{
  long n;

#if defined(_OPENMP)
#pragma omp parallel for default(none) shared(nlats, lats)
#endif
  for ( n = 0; n < nlats; ++n )
    {
      if ( lats[n] >  PIH ) lats[n] =  PIH;
      if ( lats[n] < -PIH ) lats[n] = -PIH;
    }
}
