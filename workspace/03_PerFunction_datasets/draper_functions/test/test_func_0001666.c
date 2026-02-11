init_live_reload_and_inheritance_pseudos (void)
{
  int i, p, max_regno = max_reg_num ();
  lra_live_range_t r;

  conflict_reload_and_inheritance_pseudos = sparseset_alloc (max_regno);
  live_reload_and_inheritance_pseudos = XNEWVEC (bitmap_head, lra_live_max_point);
  bitmap_obstack_initialize (&live_reload_and_inheritance_pseudos_bitmap_obstack);
  for (p = 0; p < lra_live_max_point; p++)
    bitmap_initialize (&live_reload_and_inheritance_pseudos[p],
		       &live_reload_and_inheritance_pseudos_bitmap_obstack);
  for (i = lra_constraint_new_regno_start; i < max_regno; i++)
    {
      for (r = lra_reg_info[i].live_ranges; r != NULL; r = r->next)
	for (p = r->start; p <= r->finish; p++)
	  bitmap_set_bit (&live_reload_and_inheritance_pseudos[p], i);
    }
}
