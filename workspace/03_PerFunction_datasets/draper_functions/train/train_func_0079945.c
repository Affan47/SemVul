sym_less_or_equal(int s1, int s2, struct symdata *table)
{
  if (s1 == s2)
    return TRUE;
  else {
    Ilist p;
    for (p = table[s2].dependents; p; p = p->next)
      if (sym_less_or_equal(s1, p->i, table))
	return TRUE;
    return FALSE;
  }
}
