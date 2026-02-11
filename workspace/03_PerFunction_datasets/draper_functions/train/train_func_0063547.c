or_predicates (conditions conditions,
	       struct predicate *p, struct predicate *p2)
{
  struct predicate out = true_predicate ();
  int i, j;


  if (false_predicate_p (p2) || true_predicate_p (p))
    return *p;
  if (false_predicate_p (p) || true_predicate_p (p2))
    return *p2;
  if (predicates_equal_p (p, p2))
    return *p;


  for (i = 0; p->clause[i]; i++)
    for (j = 0; p2->clause[j]; j++)
      {
	gcc_checking_assert (i < MAX_CLAUSES && j < MAX_CLAUSES);
	add_clause (conditions, &out, p->clause[i] | p2->clause[j]);
      }
  return out;
}
