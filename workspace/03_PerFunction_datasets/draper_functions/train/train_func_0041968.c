arith_decode_init(struct jbg_ardec_state *s, int reuse_st)
{
  int i;

  if (!reuse_st)
    for (i = 0; i < 4096; s->st[i++] = 0);
  s->c = 0;
  s->a = 1;
  s->ct = 0;
  s->startup = 1;
  s->nopadding = 0;
  return;
}
