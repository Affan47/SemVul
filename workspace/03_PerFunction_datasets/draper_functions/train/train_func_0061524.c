unpackInt32(unsigned char *cp, unsigned INT32 *up, long bc, long tc)
{
  U_BYTEORDER;
  unsigned char *cp0;
  unsigned INT32 *up0;
  unsigned INT32 *ip0, *ip1, *ip2, *ip3;
  long head, trail, inner, i, j;
  long offset;
  long ipack = sizeof(INT32);


  head = ( (long) cp ) & (ipack-1);
  if ( head != 0 ) head = ipack - head;
  if ( head > bc ) head = bc;

  inner = bc - head;


  trail = inner & (ipack-1);


  inner -= trail;
  inner /= ipack;

  ip0 = up + head;
  ip1 = ip0 + 1;
  ip2 = ip0 + 2;
  ip3 = ip0 + 3;

  up0 = (unsigned INT32 *) (cp + head);


  for ( i = 0 ; i < head ; i++ ) up[i] = (unsigned INT32) cp[i];

  j = 0;

  if ( IS_BIGENDIAN() )
    {
#if defined (CRAY)
#pragma _CRI ivdep
#endif
#if defined (SX)
#pragma vdir nodep
#endif
#ifdef __uxpch__
#pragma loop novrec
#endif
      for ( i = 0 ; i < inner ; i++ )
	{
	  ip0[j] = (up0[i] >> 24) & 0xFF;
	  ip1[j] = (up0[i] >> 16) & 0xFF;
	  ip2[j] = (up0[i] >>  8) & 0xFF;
	  ip3[j] = (up0[i])       & 0xFF;

	  j += ipack;
	}
    }
  else
    {
      for ( i = 0 ; i < inner ; i++ )
	{
	  ip3[j] = (up0[i] >> 24) & 0xFF;
	  ip2[j] = (up0[i] >> 16) & 0xFF;
	  ip1[j] = (up0[i] >>  8) & 0xFF;
	  ip0[j] = (up0[i])       & 0xFF;

	  j += ipack;
	}
    }

  if ( trail > 0 )
    {
      offset = head + ipack*inner;
      cp0 = cp + offset;
      for ( i = 0 ; i < trail ; i++ ) up[i+offset] = (unsigned INT32) cp0[i];
    }


  return (bc);
}
