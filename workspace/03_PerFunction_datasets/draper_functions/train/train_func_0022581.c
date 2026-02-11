all_safe(Term t, int domain_size)
{
  if (VARIABLE(t))
    return TRUE;
  else if (!top_safe(t, domain_size))
    return FALSE;
  else {
    int i;
    for (i = 0; i < ARITY(t); i++) {
      if (!all_safe(ARG(t,i), domain_size))
	return FALSE;
    }
    return TRUE;
  }
}
