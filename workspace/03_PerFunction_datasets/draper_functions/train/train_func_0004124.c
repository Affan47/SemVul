ira_build (void)
{
  bool loops_p;

  df_analyze ();
  initiate_cost_vectors ();
  initiate_allocnos ();
  initiate_copies ();
  create_loop_tree_nodes ();
  form_loop_tree ();
  create_allocnos ();
  ira_costs ();
  create_allocno_objects ();
  ira_create_allocno_live_ranges ();
  remove_unnecessary_regions (false);
  ira_compress_allocno_live_ranges ();
  update_bad_spill_attribute ();
  loops_p = more_one_region_p ();
  if (loops_p)
    {
      propagate_allocno_info ();
      create_caps ();
    }
  ira_tune_allocno_costs ();
#ifdef ENABLE_IRA_CHECKING
  check_allocno_creation ();
#endif
  setup_min_max_allocno_live_range_point ();
  sort_conflict_id_map ();
  setup_min_max_conflict_allocno_ids ();
  ira_build_conflicts ();
  update_conflict_hard_reg_costs ();
  if (! ira_conflicts_p)
    {
      ira_allocno_t a;
      ira_allocno_iterator ai;


      if (loops_p)
	{
	  remove_unnecessary_regions (true);
	  loops_p = false;
	}


      FOR_EACH_ALLOCNO (a, ai)
	if (ALLOCNO_CALLS_CROSSED_NUM (a) != 0)
	  ior_hard_reg_conflicts (a, &call_used_reg_set);
    }
  if (internal_flag_ira_verbose > 2 && ira_dump_file != NULL)
    print_copies (ira_dump_file);
  if (internal_flag_ira_verbose > 0 && ira_dump_file != NULL)
    {
      int n, nr, nr_big;
      ira_allocno_t a;
      live_range_t r;
      ira_allocno_iterator ai;

      n = 0;
      nr = 0;
      nr_big = 0;
      FOR_EACH_ALLOCNO (a, ai)
	{
	  int j, nobj = ALLOCNO_NUM_OBJECTS (a);

	  if (nobj > 1)
	    nr_big++;
	  for (j = 0; j < nobj; j++)
	    {
	      ira_object_t obj = ALLOCNO_OBJECT (a, j);
	      n += OBJECT_NUM_CONFLICTS (obj);
	      for (r = OBJECT_LIVE_RANGES (obj); r != NULL; r = r->next)
		nr++;
	    }
	}
      fprintf (ira_dump_file, "  regions=%d, blocks=%d, points=%d\n",
	       current_loops == NULL ? 1 : VEC_length (loop_p, ira_loops.larray),
	       n_basic_blocks, ira_max_point);
      fprintf (ira_dump_file,
	       "    allocnos=%d (big %d), copies=%d, conflicts=%d, ranges=%d\n",
	       ira_allocnos_num, nr_big, ira_copies_num, n, nr);
    }
  return loops_p;
}
