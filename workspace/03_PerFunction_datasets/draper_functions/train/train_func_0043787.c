analyze_increments (slsr_cand_t first_dep, enum machine_mode mode, bool speed)
{
  unsigned i;

  for (i = 0; i < incr_vec_len; i++)
    {
      HOST_WIDE_INT incr = incr_vec[i].incr.to_shwi ();


      if (!incr_vec[i].incr.fits_shwi () || !incr_vec[i].count)
	incr_vec[i].cost = COST_INFINITE;


      else if (incr == 0
	       || incr == 1
	       || (incr == -1
		   && (gimple_assign_rhs_code (first_dep->cand_stmt)
		       != POINTER_PLUS_EXPR)))
	incr_vec[i].cost = COST_NEUTRAL;


      else if (!incr_vec[i].initializer
	       && TREE_CODE (first_dep->stride) != INTEGER_CST
	       && !legal_cast_p_1 (first_dep->stride,
				   gimple_assign_lhs (first_dep->cand_stmt)))

	incr_vec[i].cost = COST_INFINITE;


      else if (!incr_vec[i].initializer
	       && TREE_CODE (first_dep->stride) != INTEGER_CST
	       && POINTER_TYPE_P (TREE_TYPE (first_dep->stride)))

	incr_vec[i].cost = COST_INFINITE;


      else if (first_dep->kind == CAND_MULT)
	{
	  int cost = mult_by_coeff_cost (incr, mode, speed);
	  int repl_savings = mul_cost (speed, mode) - add_cost (speed, mode);
	  if (speed)
	    cost = lowest_cost_path (cost, repl_savings, first_dep,
				     incr_vec[i].incr);
	  else
	    cost -= total_savings (repl_savings, first_dep, incr_vec[i].incr);

	  incr_vec[i].cost = cost;
	}


      else
	{
	  int cost = 0;
	  if (!incr_vec[i].initializer)
	    cost = mult_by_coeff_cost (incr, mode, speed);

	  if (speed)
	    cost = lowest_cost_path (cost, 0, first_dep, incr_vec[i].incr);
	  else
	    cost -= total_savings (0, first_dep, incr_vec[i].incr);

	  incr_vec[i].cost = cost;
	}
    }
}
