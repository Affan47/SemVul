recolor_spills ()
{
  unsigned int i, num;
  struct web **order2web;
  num = num_webs - num_subwebs;
  order2web = (struct web **) xmalloc (num * sizeof (order2web[0]));
  for (i = 0; i < num; i++)
    {
      order2web[i] = id2web[i];


      if (!flag_ra_merge_spill_costs && id2web[i]->type == COALESCED)
	alias (id2web[i])->spill_cost += id2web[i]->spill_cost;
    }
  qsort (order2web, num, sizeof (order2web[0]), comp_webs_maxcost);
  insert_coalesced_conflicts ();
  dump_graph_cost (DUMP_COSTS, "before spill-recolor");
  for (i = 0; i < num; i++)
    {
      struct web *web = order2web[i];
      if (web->type == SPILLED)
	try_recolor_web (web);
    }


  assign_colors ();
  free (order2web);
}
