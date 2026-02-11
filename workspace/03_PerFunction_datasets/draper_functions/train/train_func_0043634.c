merge(Term t)
{

  if (!OR_TERM(t))
    return t;
  else {
    ARG(t,1) = merge(ARG(t,1));
    if (!member(ARG(t,0), ARG(t,1)))
      return t;
    else {
      Term t1 = ARG(t,1);
      zap_mterm(ARG(t,0));
      free_term(t);
      return t1;
    }
  }
}
