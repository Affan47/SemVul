tree_call_cdce (void)
{
  basic_block bb;
  gimple_stmt_iterator i;
  bool something_changed = false;
  VEC (gimple, heap) *cond_dead_built_in_calls = NULL;
  FOR_EACH_BB (bb)
    {

      for (i = gsi_start_bb (bb); !gsi_end_p (i); gsi_next (&i))
        {
	  gimple stmt = gsi_stmt (i);
          if (is_gimple_call (stmt)
              && is_call_dce_candidate (stmt))
            {
              if (dump_file && (dump_flags & TDF_DETAILS))
                {
                  fprintf (dump_file, "Found conditional dead call: ");
                  print_gimple_stmt (dump_file, stmt, 0, TDF_SLIM);
                  fprintf (dump_file, "\n");
                }
	      if (cond_dead_built_in_calls == NULL)
		cond_dead_built_in_calls = VEC_alloc (gimple, heap, 64);
	      VEC_safe_push (gimple, heap, cond_dead_built_in_calls, stmt);
            }
	}
    }

  if (cond_dead_built_in_calls == NULL)
    return 0;

  something_changed
    = shrink_wrap_conditional_dead_built_in_calls (cond_dead_built_in_calls);

  VEC_free (gimple, heap, cond_dead_built_in_calls);

  if (something_changed)
    {
      free_dominance_info (CDI_DOMINATORS);
      free_dominance_info (CDI_POST_DOMINATORS);


      mark_sym_for_renaming (gimple_vop (cfun));
      return (TODO_update_ssa | TODO_cleanup_cfg | TODO_ggc_collect
              | TODO_remove_unused_locals);
    }
  else
    return 0;
}
