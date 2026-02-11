formula_set_variables(Formula f, int max_vars)
{
  char *a[MAX_VARS], **vmap;
  int i;

  if (max_vars > MAX_VARS)
    vmap = malloc((max_vars * sizeof(char *)));
  else
    vmap = a;

  for (i = 0; i < max_vars; i++)
    vmap[i] = NULL;

  formula_set_vars_recurse(f, vmap, max_vars);


  if (f->attributes) {
    set_vars_attributes(f->attributes, vmap, max_vars);
#if 0

    Plist attr_vars = vars_in_attributes(c->attributes);
    Plist formula_vars = vars_in_formula(c);
    if (!plist_subset(attr_vars, formula_vars)) {
      Plist p;
      printf("Variables in answers must also occur ordinary literals:\n");
      p_formula(c);
      for (p = attr_vars; p; p = p->next) {
	if (!plist_member(formula_vars, p->v)) {
	  Term t = p->v;
	  printf("Answer variable not in ordinary literal: %s.\n",
		 vmap[VARNUM(t)]);
	}
      }
      fatal_error("formula_set_variables, answer variable not in literal");
    }
    zap_plist(formula_vars);
    zap_plist(attr_vars);
#endif
  }

  if (max_vars > MAX_VARS)
    free(vmap);

}
