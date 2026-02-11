checkSize(ClpEntry *ce)  {
  bool  err;
  int  i;

  i = clpEntry_iGetInt(ce, &err);
  return(!err && (i >= 2) && (i <= GOBOARD_MAXSIZE));
}
