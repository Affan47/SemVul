member(Term x, Term t)
{

  if (term_ident(x,t))
    return TRUE;
  else if (!OR_TERM(t))
    return FALSE;
  else if (member(x,ARG(t,0)))
    return TRUE;
  else
    return member(x,ARG(t,1));
}
