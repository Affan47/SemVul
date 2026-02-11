alias_sets_must_conflict_p (alias_set_type set1, alias_set_type set2)
{
  if (set1 == 0 || set2 == 0 || set1 == set2)
    return 1;

  return 0;
}
