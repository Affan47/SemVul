execute_cleanup_eh_1 (void)
{


  remove_unreachable_handlers ();


  if (cfun->eh->region_tree)
    {
      bool changed = false;

      if (optimize)
	changed |= unsplit_all_eh ();
      changed |= cleanup_all_empty_eh ();

      if (changed)
	{
	  free_dominance_info (CDI_DOMINATORS);
	  free_dominance_info (CDI_POST_DOMINATORS);


	  delete_unreachable_blocks ();


	  remove_unreachable_handlers_no_lp ();

	  return TODO_cleanup_cfg | TODO_update_ssa_only_virtuals;
	}
    }

  return 0;
}
