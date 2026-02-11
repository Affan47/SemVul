dasharray ( const double* dasharray_ )
{
  _dasharray=(double *) RelinquishMagickMemory(_dasharray);

  if(dasharray_)
    {

      size_t n = 0;
      {
        const double *p = dasharray_;
        while(*p++ != 0)
          n++;
      }
      _size = n;


      _dasharray=static_cast<double*>(AcquireMagickMemory((n+1)*sizeof(double)));

      {
        double *q = _dasharray;
        const double *p = dasharray_;
        while( *p )
          *q++=*p++;
        *q=0;
      }
    }
}
