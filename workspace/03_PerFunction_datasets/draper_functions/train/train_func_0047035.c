kbo_weight(Term t)
{
  if (VARIABLE(t))
    return 1;
  else {
    int wt = sn_to_kb_wt(SYMNUM(t));
    int i;
    for (i = 0; i < ARITY(t); i++)
      wt += kbo_weight(ARG(t,i));
    return wt;
  }
}
