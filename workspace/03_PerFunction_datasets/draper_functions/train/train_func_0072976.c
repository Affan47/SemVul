ptransfer (char *direction, long long int bytes,
	   struct timeval *t0, struct timeval *t1)
{
  struct timeval td;
  float s;
  long long bs;

  if (verbose)
    {
      tvsub (&td, t1, t0);
      s = td.tv_sec + (td.tv_usec / 1000000.);
#define nz(x)	((x) == 0 ? 1 : (x))
      bs = bytes / nz (s);
      printf ("%lld bytes %s in %.3g seconds (%lld bytes/s)\n",
	      bytes, direction, s, bs);
    }
}
