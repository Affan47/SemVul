int10_to_str(long int val,char *dst,int radix)
{
  char buffer[65];
  register char *p;
  long int new_val;
  unsigned long int uval = (unsigned long int) val;

  if (radix < 0)
  {
    if (val < 0)
    {
      *dst++ = '-';

      uval = (unsigned long int)0 - uval;
    }
  }

  p = &buffer[sizeof(buffer)-1];
  *p = '\0';
  new_val= (long) (uval / 10);
  *--p = '0'+ (char) (uval - (unsigned long) new_val * 10);
  val = new_val;

  while (val != 0)
  {
    new_val=val/10;
    *--p = '0' + (char) (val-new_val*10);
    val= new_val;
  }
  while ((*dst++ = *p++) != 0) ;
  return dst-1;
}
