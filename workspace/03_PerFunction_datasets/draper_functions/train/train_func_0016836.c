find_bivs (struct ivopts_data *data)
{
  gimple phi;
  tree step, type, base;
  bool found = false;
  struct loop *loop = data->current_loop;
  gimple_stmt_iterator psi;

  for (psi = gsi_start_phis (loop->header); !gsi_end_p (psi); gsi_next (&psi))
    {
      phi = gsi_stmt (psi);

      if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (PHI_RESULT (phi)))
	continue;

      step = determine_biv_step (phi);
      if (!step)
	continue;

      base = PHI_ARG_DEF_FROM_EDGE (phi, loop_preheader_edge (loop));
      base = expand_simple_operations (base);
      if (contains_abnormal_ssa_name_p (base)
	  || contains_abnormal_ssa_name_p (step))
	continue;

      type = TREE_TYPE (PHI_RESULT (phi));
      base = fold_convert (type, base);
      if (step)
	{
	  if (POINTER_TYPE_P (type))
	    step = convert_to_ptrofftype (step);
	  else
	    step = fold_convert (type, step);
	}

      set_iv (data, PHI_RESULT (phi), base, step);
      found = true;
    }

  return found;
}
