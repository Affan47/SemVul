remap_predicate_after_duplication (struct predicate *p,
				   clause_t possible_truths,
				   struct inline_summary *info)
{
  struct predicate new_predicate = true_predicate ();
  int j;
  for (j = 0; p->clause[j]; j++)
    if (!(possible_truths & p->clause[j]))
      {
	new_predicate = false_predicate ();
	break;
      }
    else
      add_clause (info->conds, &new_predicate,
		  possible_truths & p->clause[j]);
  return new_predicate;
}
