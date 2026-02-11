l1sp_printc(g, ch)
  l1sp_ctx *g;
{
  if(!ioallocp(g, (size_t)1U)) l1sp_flush(g);
  g->l1_iobuffer[g->l1_iosize++]=ch;
}
