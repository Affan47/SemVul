Seac(asb, adx, ady, bchar, achar)
  DOUBLE asb, adx, ady;
  unsigned char bchar, achar;
{
  int Code;
  long pindex = 0;

  isseac      = 1;
  seacaccent  = achar;
  seacbase    = bchar;

  IfTrace4((FontDebug), "SEAC %f %f %f %d ", asb, adx, ady, bchar);
  IfTrace1((FontDebug), "%d\n", achar);


  accentoffsetX = adx - asb;
  accentoffsetY = ady;


  path = NULL;


  CharStringP = GetType1CharString(Environment, achar);
  if (CharStringP == NULL) {
     Error1i("Invalid accent ('%03o) in SEAC\n", achar);
  }
  StartDecrypt();

  ClearStack();
  ClearPSFakeStack();
  ClearCallStack();

  for (;;) {
    if (!DoRead(&Code)) break;
    Decode(Code);
    if (errflag) return(0);
  }


  pindex = nextPPoint();
  ppoints[pindex].x       = accentoffsetX;
  ppoints[pindex].y       = accentoffsetY;
  ppoints[pindex].ax      = accentoffsetX;
  ppoints[pindex].ay      = accentoffsetY;
  ppoints[pindex].type    = PPOINT_SEAC;
  ppoints[pindex].hinted  = 0;


  accentoffsetX = accentoffsetY = 0;


  CharStringP = GetType1CharString(Environment, bchar);
  StartDecrypt();

  ClearStack();
  ClearPSFakeStack();
  ClearCallStack();

  InitStems();

  for (;;) {
    if (!DoRead(&Code)) break;
    Decode(Code);
    if (errflag) return(0);
  }

  return(0);
}
