gridGenXbounds2D(int nx, int ny, const double * restrict xbounds, double * restrict xbounds2D)
{
  long i, j, index;
  double minlon, maxlon;

#if defined(_OPENMP)
#pragma omp parallel for default(none)        \
  shared(nx, ny, xbounds, xbounds2D)	      \
  private(i, j, minlon, maxlon, index)
#endif
  for ( i = 0; i < nx; ++i )
    {
      minlon = xbounds[2*i  ];
      maxlon = xbounds[2*i+1];

      for ( j = 0; j < ny; ++j )
	{
	  index = j*4*nx + 4*i;
	  xbounds2D[index  ] = minlon;
	  xbounds2D[index+1] = maxlon;
	  xbounds2D[index+2] = maxlon;
	  xbounds2D[index+3] = minlon;
	}
    }
}
