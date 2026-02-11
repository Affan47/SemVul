Delete_Dynamic_Clause(DynCInf *clause)
{
  DynPInf *dyn;
  Bool first;

  dyn = clause->dyn;
  first = (dyn->first_erased_cl == NULL);

  clause->erase_stamp = erase_stamp;
  clause->next_erased_cl = dyn->first_erased_cl;
  dyn->first_erased_cl = clause;

  if (first)
    {
      dyn->next_dyn_with_erase = first_dyn_with_erase;
      first_dyn_with_erase = dyn;
    }

  size_of_erased += clause->term_size;
  Clean_Erased_Clauses();

#ifdef DEBUG
  Check_Dynamic_Clauses(dyn);
#endif
}
