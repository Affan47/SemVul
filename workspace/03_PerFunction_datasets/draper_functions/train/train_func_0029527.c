try_to_part(struct clause *c,
			struct clause **p1,
			struct clause **p2,
			int part_vars)
{
  int nvars = biggest_var_clause(c) + 1;
  *p1 = *p2 = NULL;

  if (nvars >= part_vars) {
    int p[MAX_LITS];
    int bp[MAX_LITS];
    int bs = INT_MAX;
    int n = num_literals(c);
    int i;

    for (i = 0; i < n; i++)
      bp[i] = p[i] = 0;

    parts(0, p, n, c, bp, &bs);

    if (bs != INT_MAX) {

      struct clause *n1 = get_clause();
      struct clause *n2 = get_clause();
      n1->id = c->id;
      n2->id = c->id;
      for (i = 0; i < n; i++) {
	struct literal *lit = copy_literal(ith_literal(c, i+1));
	if (bp[i] == 0)
	  append_literal(n1, lit);
	else
	  append_literal(n2, lit);
      }
      {
	struct literal *lit1;
	struct literal *lit2;

	int vars_1[MAX_VARS], vars_2[MAX_VARS], c_vars[MAX_VARS];

	for (i = 0; i < MAX_VARS; i++)
	  vars_1[i] = vars_2[i] = c_vars[i] = 0;

	which_vars(vars_1, n1);
	which_vars(vars_2, n2);
	intersect_vars(vars_1, vars_2, nvars, c_vars);

	lit1 = connector(c_vars, nvars);
	lit2 = copy_literal(lit1);


	if (num_pos_lits(n1) < num_pos_lits(n2))
	  { lit1->sign = 1; lit2->sign = 0; }
	else
	  { lit1->sign = 0; lit2->sign = 1; }

	append_literal(n1, lit1);
	append_literal(n2, lit2);

#if 0
	printf("\nParting clause: "); p_clause(c);
	printf("Part1:          "); p_clause(n1);
	printf("Part2:          "); p_clause(n2);
#endif

	renumber_vars(n1);
	renumber_vars(n2);
      }
      *p1 = n1;
      *p2 = n2;
    }
  }
}
