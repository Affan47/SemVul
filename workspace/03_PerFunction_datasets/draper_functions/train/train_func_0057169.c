yankable_term(struct term *t, int check)
{
  if (check && t->type != VARIABLE && !domain_element(t))
    return t;
  else {
    struct rel *r;
    struct term *t1;
    for (r = t->farg; r; r = r->narg) {
      t1 = yankable_term(r->argval, 1);
      if (t1 != NULL)
	return t1;
    }
    return NULL;
  }
}
