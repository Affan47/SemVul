free_temps_for_rtl_expr (tree t)
{
  struct temp_slot *p;

  for (p = temp_slots; p; p = p->next)
    if (p->rtl_expr == t)
      {


	if (temp_slot_level <= p->level)
	  p->in_use = 0;
	else
	  p->rtl_expr = NULL_TREE;
      }

  combine_temp_slots ();
}
