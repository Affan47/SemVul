mark_contblock(void *p, int s) {

  STATIC char *q;
  STATIC char *x, *y;
  struct pageinfo *v;

  if (NULL_OR_ON_C_STACK(p))
    return;

  q = p + s;


  x = (char *)ROUND_DOWN_PTR_CONT(p);
  y = (char *)ROUND_UP_PTR_CONT(q);
  v=get_pageinfo(x);
#ifdef SGC
  if (!sgc_enabled || (v->sgc_flags&SGC_PAGE_FLAG))
#endif
    set_mark_bits(v,x,y);
}
