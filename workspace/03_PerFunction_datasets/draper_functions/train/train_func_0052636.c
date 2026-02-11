swap4byte(void *ptr, size_t size)
{
  INT32 *ptrtmp;
  int nval;

  nval = size;
  if ( nval < 0 ) nval = 0;
  ptrtmp = (INT32 *) ptr;

  if ( sizeof(INT32) == 4 )
    {
      while ( nval-- )
	{
	  *ptrtmp = (((*ptrtmp >> 24) & 0x00ff) | ((*ptrtmp & 0x00ff) << 24) |
		     ((*ptrtmp >>  8) & 0xff00) | ((*ptrtmp & 0xff00) <<  8));
	  ptrtmp++;
	}
    }
  else
    {
      Error("not implemented for %d byte data", sizeof(INT32));
    }
}
