analyze_siv_subscript (tree chrec_a,
		       tree chrec_b,
		       conflict_function **overlaps_a,
		       conflict_function **overlaps_b,
		       tree *last_conflicts,
		       int loop_nest_num)
{
  dependence_stats.num_siv++;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(analyze_siv_subscript \n");

  if (evolution_function_is_constant_p (chrec_a)
      && evolution_function_is_affine_in_loop (chrec_b, loop_nest_num))
    analyze_siv_subscript_cst_affine (chrec_a, chrec_b,
				      overlaps_a, overlaps_b, last_conflicts);

  else if (evolution_function_is_affine_in_loop (chrec_a, loop_nest_num)
	   && evolution_function_is_constant_p (chrec_b))
    analyze_siv_subscript_cst_affine (chrec_b, chrec_a,
				      overlaps_b, overlaps_a, last_conflicts);

  else if (evolution_function_is_affine_in_loop (chrec_a, loop_nest_num)
	   && evolution_function_is_affine_in_loop (chrec_b, loop_nest_num))
    {
      if (!chrec_contains_symbols (chrec_a)
	  && !chrec_contains_symbols (chrec_b))
	{
	  analyze_subscript_affine_affine (chrec_a, chrec_b,
					   overlaps_a, overlaps_b,
					   last_conflicts);

	  if (CF_NOT_KNOWN_P (*overlaps_a)
	      || CF_NOT_KNOWN_P (*overlaps_b))
	    dependence_stats.num_siv_unimplemented++;
	  else if (CF_NO_DEPENDENCE_P (*overlaps_a)
		   || CF_NO_DEPENDENCE_P (*overlaps_b))
	    dependence_stats.num_siv_independent++;
	  else
	    dependence_stats.num_siv_dependent++;
	}
      else if (can_use_analyze_subscript_affine_affine (&chrec_a,
							&chrec_b))
	{
	  analyze_subscript_affine_affine (chrec_a, chrec_b,
					   overlaps_a, overlaps_b,
					   last_conflicts);

	  if (CF_NOT_KNOWN_P (*overlaps_a)
	      || CF_NOT_KNOWN_P (*overlaps_b))
	    dependence_stats.num_siv_unimplemented++;
	  else if (CF_NO_DEPENDENCE_P (*overlaps_a)
		   || CF_NO_DEPENDENCE_P (*overlaps_b))
	    dependence_stats.num_siv_independent++;
	  else
	    dependence_stats.num_siv_dependent++;
	}
      else
	goto siv_subscript_dontknow;
    }

  else
    {
    siv_subscript_dontknow:;
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "  siv test failed: unimplemented");
      *overlaps_a = conflict_fn_not_known ();
      *overlaps_b = conflict_fn_not_known ();
      *last_conflicts = chrec_dont_know;
      dependence_stats.num_siv_unimplemented++;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, ")\n");
}
