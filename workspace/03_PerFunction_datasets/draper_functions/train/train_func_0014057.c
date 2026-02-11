l1sp_cat(g, l)
  l1sp_ctx *g;
  l1sp *l;
{
  L1SP_PROT1_DECL(g);
  l1sp *x, *y, *r;
  char *d, *s;
  size_t n;


  n=(size_t)0U;
  for(x=l; l1sp_consp(x); x=l1sp_cdr(x)) {
    y=l1sp_car(x);
    if(!l1sp_symbolp(y)) l1sp_diebadarg(g, y);
    n+=strlen(l1sp_symbits(y));
  }


  l1sp_prot1(g, l);
  r=l1sp_alloc(g, L1SP_SYMBOL, n, &g->l1_nil, &g->l1_nil);
  l1sp_unprot1(g);


  d=l1sp_symbits(r);
  for(x=l; l1sp_consp(x); x=l1sp_cdr(x)) {
    s=l1sp_symbits(l1sp_car(x));
    memcpy(d, s, n=strlen(s));
    d+=n;
  }
  *d='\0';


  for(x=g->l1_oblist; l1sp_consp(x); x=l1sp_cdr(x)) {
    if(0==strcmp(l1sp_symbits(l1sp_car(x)), l1sp_symbits(r)))
      return l1sp_car(x);
  }

  return r;
}
