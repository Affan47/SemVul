l1sp_flush(g)
  l1sp_ctx *g;
{
  ssize_t r;
  size_t i=(size_t)0U;
  while(g->l1_iosize) {
    switch(r=(*g->l1_write)(g->l1_iofd, g->l1_iobuffer+i, g->l1_iosize)) {
    case -1:
    case 0:
      l1sp_dienowrite(g);

    default:
      i+=(size_t)r;
      g->l1_iosize-=(size_t)r;
      break;
    }
  }
  return g->l1_nil;
}
