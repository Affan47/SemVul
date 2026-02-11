get_coverage_counts (unsigned counter, unsigned expected,
                     unsigned cfg_checksum, unsigned lineno_checksum,
		     const struct gcov_ctr_summary **summary)
{
  counts_entry_t *entry, elt;


  if (!counts_hash)
    {
      static int warned = 0;

      if (!warned++)
	inform (input_location, (flag_guess_branch_prob
		 ? "file %s not found, execution counts estimated"
		 : "file %s not found, execution counts assumed to be zero"),
		da_file_name);
      return NULL;
    }

  elt.ident = current_function_funcdef_no + 1;
  elt.ctr = counter;
  entry = (counts_entry_t *) htab_find (counts_hash, &elt);
  if (!entry || !entry->summary.num)


    return NULL;

  if (entry->cfg_checksum != cfg_checksum
      || entry->summary.num != expected)
    {
      static int warned = 0;
      bool warning_printed = false;
      tree id = DECL_ASSEMBLER_NAME (current_function_decl);

      warning_printed =
	warning_at (input_location, OPT_Wcoverage_mismatch,
		    "the control flow of function %qE does not match "
		    "its profile data (counter %qs)", id, ctr_names[counter]);
      if (warning_printed)
	{
	 inform (input_location, "use -Wno-error=coverage-mismatch to tolerate "
	 	 "the mismatch but performance may drop if the function is hot");

	  if (!seen_error ()
	      && !warned++)
	    {
	      inform (input_location, "coverage mismatch ignored");
	      inform (input_location, flag_guess_branch_prob
		      ? G_("execution counts estimated")
		      : G_("execution counts assumed to be zero"));
	      if (!flag_guess_branch_prob)
		inform (input_location,
			"this can result in poorly optimized code");
	    }
	}

      return NULL;
    }
  else if (entry->lineno_checksum != lineno_checksum)
    {
      warning (0, "source locations for function %qE have changed,"
	       " the profile data may be out of date",
	       DECL_ASSEMBLER_NAME (current_function_decl));
    }

  if (summary)
    *summary = &entry->summary;

  return entry->counts;
}
