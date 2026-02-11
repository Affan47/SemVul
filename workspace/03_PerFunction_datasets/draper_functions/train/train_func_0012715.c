symbol_occurrences_in_clause(Literals lits, int symnum)
{
  if (lits == NULL)
    return 0;
  else
    return
      symbol_occurrences(lits->atom, symnum) +
      symbol_occurrences_in_clause(lits->next, symnum);
}
