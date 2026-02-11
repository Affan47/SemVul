occur_check(int vn,
		struct context *vc,
		struct term *t,
		struct context *c)
{
  if (t->type == NAME)
    return 1;
  else if (t->type == COMPLEX) {
    struct rel *r = t->farg;
    while (r != NULL && occur_check(vn, vc, r->argval, c))
      r = r->narg;
    return (r == NULL);
  }
  else {
    int tvn = t->varnum;
    if (tvn == vn && c == vc)
      return 0;
    else if (c->terms[tvn] == NULL)
      return 1;
    else
      return occur_check(vn, vc, c->terms[tvn], c->contexts[tvn]);
  }
}
