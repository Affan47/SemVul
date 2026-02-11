instantiate_scev_name (basic_block instantiate_below,
		       struct loop *evolution_loop, struct loop *inner_loop,
		       tree chrec,
		       bool fold_conversions, htab_t cache, int size_expr)
{
  tree res;
  struct loop *def_loop;
  basic_block def_bb = gimple_bb (SSA_NAME_DEF_STMT (chrec));


  if (!def_bb
      || loop_depth (def_bb->loop_father) == 0
      || dominated_by_p (CDI_DOMINATORS, instantiate_below, def_bb))
    return chrec;


  res = get_instantiated_value (cache, instantiate_below, chrec);
  if (res)
    return res;

  res = chrec_dont_know;
  set_instantiated_value (cache, instantiate_below, chrec, res);

  def_loop = find_common_loop (evolution_loop, def_bb->loop_father);


  res = analyze_scalar_evolution (def_loop, chrec);


  if (TREE_CODE (res) == SSA_NAME
      && SSA_NAME_IS_DEFAULT_DEF (res))
    ;


  else if (TREE_CODE (res) == SSA_NAME
	   && loop_depth (loop_containing_stmt (SSA_NAME_DEF_STMT (res)))
	   > loop_depth (def_loop))
    {
      if (res == chrec)
	res = loop_closed_phi_def (chrec);
      else
	res = chrec;


      if (res == NULL_TREE)
	{
	  loop_p loop = loop_containing_stmt (SSA_NAME_DEF_STMT (chrec));
	  res = analyze_scalar_evolution (loop, chrec);
	  res = compute_overall_effect_of_inner_loop (loop, res);
	  res = instantiate_scev_r (instantiate_below, evolution_loop,
				    inner_loop, res,
				    fold_conversions, cache, size_expr);
	}
      else if (!dominated_by_p (CDI_DOMINATORS, instantiate_below,
				gimple_bb (SSA_NAME_DEF_STMT (res))))
	res = chrec_dont_know;
    }

  else if (res != chrec_dont_know)
    {
      if (inner_loop
	  && !flow_loop_nested_p (def_bb->loop_father, inner_loop))

	res = chrec_dont_know;
      else
	res = instantiate_scev_r (instantiate_below, evolution_loop,
				  inner_loop, res,
				  fold_conversions, cache, size_expr);
    }


  set_instantiated_value (cache, instantiate_below, chrec, res);
  return res;
}
