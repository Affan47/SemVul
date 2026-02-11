free_lits_to_term(Term t)
{
  if (SYMNUM(t) == not_symnum())
    free_term(t);
  else if (SYMNUM(t) == or_symnum()) {
    free_lits_to_term(ARG(t,0));
    free_lits_to_term(ARG(t,1));
    free_term(t);
  }
}
