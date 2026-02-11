int2str(register long int val, register char *dst, register int radix,
        int upcase)
{
  char buffer[65];
  register char *p;
  long int new_val;
  char *dig_vec= upcase ? _dig_vec_upper : _dig_vec_lower;
  ulong uval= (ulong) val;

  if (radix < 0)
  {
    if (radix < -36 || radix > -2)
      return NullS;
    if (val < 0)
    {
      *dst++ = '-';

      uval = (ulong)0 - uval;
    }
    radix = -radix;
  }
  else if (radix > 36 || radix < 2)
    return NullS;


  p = &buffer[sizeof(buffer)-1];
  *p = '\0';
  new_val= uval / (ulong) radix;
  *--p = dig_vec[(uchar) (uval- (ulong) new_val*(ulong) radix)];
  val = new_val;
#ifdef HAVE_LDIV
  while (val != 0)
  {
    ldiv_t res;
    res=ldiv(val,radix);
    *--p = dig_vec[res.rem];
    val= res.quot;
  }
#else
  while (val != 0)
  {
    new_val=val/radix;
    *--p = dig_vec[(uchar) (val-new_val*radix)];
    val= new_val;
  }
#endif
  while ((*dst++ = *p++) != 0) ;
  return dst-1;
}
