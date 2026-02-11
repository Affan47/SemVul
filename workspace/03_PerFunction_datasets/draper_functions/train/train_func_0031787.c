inflate_block(__G__ e)
  __GDEF
  int *e;

{
  unsigned t;
  register ulg b;
  register unsigned k;
  int retval = 0;


  b = G.bb;
  k = G.bk;


  NEEDBITS(1)
  *e = (int)b & 1;
  DUMPBITS(1)


  NEEDBITS(2)
  t = (unsigned)b & 3;
  DUMPBITS(2)


  G.bb = b;
  G.bk = k;


  if (t == 2)
    return inflate_dynamic(__G);
  if (t == 0)
    return inflate_stored(__G);
  if (t == 1)
    return inflate_fixed(__G);


  retval = 2;

cleanup_and_exit:
  return retval;
}
