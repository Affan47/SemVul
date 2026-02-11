renum_vars_recurse(Term t, int vmap[], int max_vars)
{
  if (VARIABLE(t)) {
    int i = 0;
    while (i < max_vars && vmap[i] != -1 && vmap[i] != VARNUM(t))
      i++;
    if (i == max_vars)
      fatal_error("renum_vars_recurse: too many variables");

    if (vmap[i] == -1)
      vmap[i] = VARNUM(t);
    free_term(t);
    return get_variable_term(i);
  }
  else {
    int i;
    for (i = 0; i < ARITY(t); i++)
      ARG(t,i) = renum_vars_recurse(ARG(t,i), vmap, max_vars);
    return t;
  }
}
