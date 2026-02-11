p_atomp(g, l)
  l1sp_ctx *g;
  l1sp *l;
{
  if(l1sp_consp(l)) return g->l1_nil;
  return g->l1_t;
}
