Add_To_2Chain(D2ChHdr *hdr, DynCInf *clause, Bool in_seq_chain, Bool asserta)
{
  D2ChCell *cell = (in_seq_chain) ? &clause->seq_chain : &clause->ind_chain;

  if (hdr->first == NULL)
    {
      hdr->first = hdr->last = clause;
      cell->next = cell->prev = NULL;
      return;
    }

  if (asserta)
    {
      cell->next = hdr->first;
      cell->prev = NULL;
      hdr->first = clause;
      if (in_seq_chain)
	cell->next->seq_chain.prev = clause;
      else
	cell->next->ind_chain.prev = clause;
    }
  else
    {
      if (in_seq_chain)
	hdr->last->seq_chain.next = clause;
      else
	hdr->last->ind_chain.next = clause;
      cell->next = NULL;
      cell->prev = hdr->last;
      hdr->last = clause;
    }
}
