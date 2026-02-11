process_negative_equalities(struct clause *c)
{
  struct literal *curr, *prev, *l;
  struct term *t1, *t2, *v, *t;

  t = NULL;

  curr = c->first_lit;
  prev = NULL;
  while (curr) {
    if (is_eq(curr->atom->sym_num) && !curr->sign) {
      t1 = curr->atom->farg->argval;
      t2 = curr->atom->farg->narg->argval;
      v = NULL;
      if (t1->type == VARIABLE && !occurs_in(t1, t2)) {
	v = t1; t = t2;
      }
      else if (t2->type == VARIABLE && !occurs_in(t2, t1)) {
	v = t2; t = t1;
      }

      if (v) {
	if (prev)
	  prev->next_lit = curr->next_lit;
	else
	  c->first_lit = curr->next_lit;
	for (l = c->first_lit; l; l = l->next_lit)
	  l->atom = replace_term(l->atom, v, t);
      }
      else
	prev = curr;
    }
    else
      prev = curr;

    curr = curr->next_lit;
  }
}
