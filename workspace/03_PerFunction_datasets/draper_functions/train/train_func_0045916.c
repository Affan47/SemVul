which_vars_part(int *vars,
			    struct clause *c,
			    int *part,
			    int to_check)
{
  struct literal *lit;
  int i;
  for (lit = c->first_lit, i = 0; lit; lit = lit->next_lit, i++) {
    if (part[i] == to_check)
      which_vars_term(vars, lit->atom);
  }
}
