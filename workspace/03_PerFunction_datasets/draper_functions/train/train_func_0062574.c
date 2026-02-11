move(g, s)
  l1sp_ctx *g;
  l1sp *s;
{
  l1sp *x=g->l1_nil;
  size_t n;

  switch(l1sp_tag(s)) {
  case L1SP_NIL:
    x=s;
    break;

  case L1SP_FORM0:
  case L1SP_PROC0:
  case L1SP_FORMN:
  case L1SP_PROCN:
    x=l1sp_alloc(g, l1sp_tag(s), (size_t)0U, &g->l1_nil, &g->l1_nil);
    ((l1sp_func*)x)->l1_func=((l1sp_func*)s)->l1_func;
    forward(s, x);
    break;

  case L1SP_MACRO:
  case L1SP_LAMBDA:
  case L1SP_PAIR:
    x=l1sp_alloc(g, l1sp_tag(s), (size_t)0U, &g->l1_nil, &g->l1_nil);
    l1sp_rplaca(x, l1sp_car(s));
    l1sp_rplacd(x, l1sp_cdr(s));
    forward(s, x);
    break;

  case L1SP_SYMBOL:
    x=l1sp_alloc(g,
                 l1sp_tag(s),
                 n=strlen(l1sp_symbits(s)),
                 &g->l1_nil,
                 &g->l1_nil);
    memcpy(l1sp_symbits(x), l1sp_symbits(s), n+(size_t)1U);
    g->l1_oblist=l1sp_cons(g, x, g->l1_oblist);
    forward(s, x);
    break;

  case L1SP_FORWARD:
    x=s->l1_forward;
    break;
  }

  return x;
}
