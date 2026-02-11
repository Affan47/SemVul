simp_term(Term t)
{
  if (VARIABLE(t))
    return t;
  else {
    int i, id;
    for (i = 0; i < ARITY(t); i++)
      ARG(t,i) = simp_term(ARG(t,i));
    if (eterm(t, &id) && Cells[id].value != NULL) {
      zap_mterm(t);
      return Cells[id].value;
    }
    else
      return t;
  }
}
