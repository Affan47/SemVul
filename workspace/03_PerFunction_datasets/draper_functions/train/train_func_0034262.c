calculate_count(long s, long e)
{
      unsigned long r;
      if (s >= e) {
	    r = s - e;
      } else {
	    r = e - s;
      }
      if (r >= UINT_MAX) {
	    return 0;
      }
      return r + 1;
}
