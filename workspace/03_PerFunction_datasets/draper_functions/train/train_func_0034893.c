raninit( ranctx *x, u4 seed ) {
  u4 i, e;
  x->a = x->b = x->c = 0xf1ea5eed;
  x->d = seed - x->a;
  for (i=0; i<20; ++i) {
    e = ranval(x);
  }
  return e;
}
