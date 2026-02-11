FuncINTFLOOR_MACFLOAT( Obj self, Obj obj )
{
#if HAVE_TRUNC
  Double f = trunc(VAL_MACFLOAT(obj));
#else
  Double f = VAL_MACFLOAT(obj);
  if (f >= 0.0)
    f = floor(f);
  else
    f = -floor(-f);
#endif


  if (fabs(f) < (Double) (1L<<NR_SMALL_INT_BITS))
    return INTOBJ_INT((Int)f);

  int str_len = (int) (log(fabs(f)) / log(16.0)) + 3;

  Obj str = NEW_STRING(str_len);
  char *s = CSTR_STRING(str), *p = s+str_len-1;
  if (f < 0.0)
    f = -f, s[0] = '-';
  while (p > s || (p == s && s[0] != '-')) {
    int d = (int) fmod(f,16.0);
    *p-- = d < 10 ? '0'+d : 'a'+d-10;
    f /= 16.0;
  }
  return FuncIntHexString(self,str);
}
