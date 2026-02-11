remove_from_table (struct table_elt *elt, unsigned int hash)
{
  if (elt == 0)
    return;


  elt->first_same_value = 0;


  {
    struct table_elt *prev = elt->prev_same_value;
    struct table_elt *next = elt->next_same_value;

    if (next)
      next->prev_same_value = prev;

    if (prev)
      prev->next_same_value = next;
    else
      {
	struct table_elt *newfirst = next;
	while (next)
	  {
	    next->first_same_value = newfirst;
	    next = next->next_same_value;
	  }
      }
  }


  {
    struct table_elt *prev = elt->prev_same_hash;
    struct table_elt *next = elt->next_same_hash;

    if (next)
      next->prev_same_hash = prev;

    if (prev)
      prev->next_same_hash = next;
    else if (table[hash] == elt)
      table[hash] = next;
    else
      {


	for (hash = 0; hash < HASH_SIZE; hash++)
	  if (table[hash] == elt)
	    table[hash] = next;
      }
  }


  if (elt->related_value != 0 && elt->related_value != elt)
    {
      struct table_elt *p = elt->related_value;

      while (p->related_value != elt)
	p = p->related_value;
      p->related_value = elt->related_value;
      if (p->related_value == p)
	p->related_value = 0;
    }


  elt->next_same_hash = free_element_chain;
  free_element_chain = elt;
}
