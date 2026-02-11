yankable(struct clause *c)
{
  struct literal *lit;
  struct term *t = NULL;

  for (lit = c->first_lit; lit; lit = lit->next_lit) {
    struct term *a = lit->atom;
    if (!is_eq(a->sym_num))
      t = yankable_term(a, 0);
    else {
      t = yankable_term(a->farg->argval, 0);
      if (t == NULL)
	t = yankable_term(a->farg->narg->argval, 1);
    }
    if (t != NULL)
      return t;
  }
  return NULL;
}
