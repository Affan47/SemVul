xx_resolvable(struct clause *c)
{
  if (unit_clause(c))
    return(0);
  else {
    struct literal *lit;

    lit = c->first_lit;
    while (lit) {
      if (!lit->sign && is_eq(lit->atom->sym_num)) {
	struct term *a1 = lit->atom->farg->argval;
	struct term *a2 = lit->atom->farg->narg->argval;
	if (a1->type == VARIABLE && !occurs_in(a1, a2))
	  return(1);
	else if (a2->type == VARIABLE && !occurs_in(a2, a1))
	  return(1);
      }
      lit = lit->next_lit;
    }
    return(0);
  }
}
