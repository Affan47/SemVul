form_reserv_sets_list (pattern_set_el_t pattern_list)
{
  pattern_set_el_t el;
  pattern_reserv_t first, curr, prev;
  int i;

  prev = first = NULL;
  for (el = pattern_list; el != NULL; el = el->next_pattern_set_el)
    {
      curr = create_node (sizeof (struct pattern_reserv));
      curr->reserv = alloc_empty_reserv_sets ();
      curr->next_pattern_reserv = NULL;
      for (i = 0; i < el->units_num; i++)
	{
	  SET_BIT (curr->reserv, el->unit_decls [i]->unit_num);
	  el->unit_decls [i]->in_set_p = TRUE;
	}
      if (prev != NULL)
	prev->next_pattern_reserv = curr;
      else
	first = curr;
      prev = curr;
    }
  return first;
}
