inflate_fixed_setup(
  struct InflateState *is
)
{
  int i;
  struct huft *tl;
  struct huft *td;
  int bl;
  int bd;
  unsigned l[288];


  for (i = 0; i < 144; i++)
    l[i] = 8;
  for (; i < 256; i++)
    l[i] = 9;
  for (; i < 280; i++)
    l[i] = 7;
  for (; i < 288; i++)
    l[i] = 8;
  bl = 7;
  if ((i = huft_build(is, l, 288, 257, cplens, cplext, &tl, &bl)) != 0)
    return i;


  for (i = 0; i < 30; i++)
    l[i] = 5;
  bd = 5;
  if ((i = huft_build(is, l, 30, 0, cpdist, cpdext, &td, &bd)) > 1)
  {
    huft_free(is, tl);
    return i;
  }


  is->tl = tl;
  is->td = td;
  is->bl = bl;
  is->bd = bd;

  return 0;
}
