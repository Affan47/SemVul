renum_vars_map(Topform c)
{
  int a[MAX_VARS];
  int i;
  Literals lit;
  Plist pairs = NULL;

  for (i = 0; i < MAX_VARS; i++)
    a[i] = -1;

  for (lit = c->literals; lit != NULL; lit = lit->next)
    lit->atom = renum_vars_recurse(lit->atom, a, MAX_VARS);


  renumber_vars_attributes(c->attributes, a, MAX_VARS);


  for (i = 0; i < MAX_VARS; i++) {

    if (a[i] != -1 && a[i] != i) {
      Term v1 = get_variable_term(a[i]);
      Term v2 = get_variable_term(i);
      Term pair = listterm_cons(v1, v2);
      pairs = plist_append(pairs, pair);
    }
  }
  c->normal_vars = TRUE;
  return pairs;
}
