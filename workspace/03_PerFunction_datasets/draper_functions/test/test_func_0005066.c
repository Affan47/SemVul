complex4_compare(Term a, Term b, int *n)
{


  if (VARIABLE(a) && VARIABLE(b)) {
    if (VARNUM(a) == VARNUM(b))
      (*n)++;
  }
  else if (!VARIABLE(a) && !VARIABLE(b)) {
    if (SYMNUM(a) == SYMNUM(b)) {
      int i;
      (*n)++;
      for (i = 0; i < ARITY(a); i++)
	complex4_compare(ARG(a,i), ARG(b,i), n);
    }
  }
}
