args_distinct_vars(Term t)
{
#if 1
  if (VARIABLE(t))
    return FALSE;
  else {
    int i;
    for (i = 0; i < ARITY(t); i++) {
      if (!VARIABLE(ARG(t,i)))
	return FALSE;
      else {
	int j;
	for (j = 0; j < i; j++)
	  if (VARNUM(ARG(t,i)) == VARNUM(ARG(t,j)))
	    return FALSE;
      }
    }
    return TRUE;
  }
#else
  if (VARIABLE(t))
    return FALSE;
  else {
    int *p = calloc(ARITY(t), sizeof(int));
    int i;
    BOOL ok = TRUE;
    for (i = 0; i < ARITY(t) && ok; i++) {
      Term s = ARG(t,i);
      if (!VARIABLE(s))
	ok = FALSE;
      else if (p[VARNUM(s)])
	ok = FALSE;
      else
	p[VARNUM(s)] = TRUE;
    }
    free(p);
    return ok;
  }
#endif
}
