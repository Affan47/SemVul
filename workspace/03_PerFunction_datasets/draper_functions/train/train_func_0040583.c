decContextTestEndian(Flag quiet) {
  Int res=0;
  uInt dle=(uInt)DECLITEND;
  if (dle>1) dle=1;

  if (LITEND!=DECLITEND) {
    if (!quiet) {
#if DECCHECK
      const char *adj;
      if (LITEND) adj="little";
	     else adj="big";
      printf("Warning: DECLITEND is set to %d, but this computer appears to be %s-endian\n",
	     DECLITEND, adj);
#endif
      }
    res=(Int)LITEND-dle;
    }
  return res;
  }
