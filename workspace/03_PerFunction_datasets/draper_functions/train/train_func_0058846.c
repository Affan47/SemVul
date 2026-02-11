FuncREVNEG_STRING (
    Obj             self,
    Obj             val )
{
  UInt l,i,j;
  Obj n;
  UInt1 *p,*q;


  while (! IsStringConv(val)) {
     val = ErrorReturnObj(
         "<val> must be a string, not a %s)",
         (Int)TNAM_OBJ(val), 0L,
         "you can replace <val> via 'return <val>;'" );
  }

  l=GET_LEN_STRING(val);
  n=NEW_STRING(l);
  SET_LEN_STRING(n,l);
  p=CHARS_STRING(val);
  q=CHARS_STRING(n);
  j=l-1;
  for (i=1;i<=l;i++) {

    *q++=-p[j];
    j--;
  }

  CHANGED_BAG(n);
  return n;
}
