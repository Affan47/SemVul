write_state_pair_list (pair_p list)
{
  int nbpair = 0;
  pair_p current;

  for (current = list; current != NULL; current = current->next)
    {
      write_state_pair (current);
      nbpair++;
    }
  return nbpair;

}
