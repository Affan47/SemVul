zap_term(Term t)
{
  int i;
  for (i = 0; i < ARITY(t); i++)
    zap_term(ARG(t,i));
  free_term(t);
}
