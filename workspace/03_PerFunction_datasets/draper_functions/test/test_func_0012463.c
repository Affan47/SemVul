form_the_same_automaton_unit_lists_from_regexp (regexp)
     regexp_t regexp;
{
  int i, j, k;
  regexp_t seq, allof, unit;

  if (regexp == NULL || regexp->mode != rm_oneof)
    return;
  for (i = 0; i < description->max_insn_reserv_cycles; i++)
    the_same_automaton_lists [i] = NULL;
  for (i = REGEXP_ONEOF (regexp)->regexps_num - 1; i >= 0; i--)
    {
      seq = REGEXP_ONEOF (regexp)->regexps [i];
      if (seq->mode == rm_sequence)
	for (j = 0; j < REGEXP_SEQUENCE (seq)->regexps_num; j++)
	  {
	    allof = REGEXP_SEQUENCE (seq)->regexps [j];
	    if (allof->mode == rm_allof)
	      for (k = 0; k < REGEXP_ALLOF (allof)->regexps_num; k++)
		{
		  unit = REGEXP_ALLOF (allof)->regexps [k];
		  if (unit->mode == rm_unit)
		    process_unit_to_form_the_same_automaton_unit_lists
		      (unit, regexp, j);
		  else if (unit->mode != rm_nothing)
		    abort ();
		}
	    else if (allof->mode == rm_unit)
	      process_unit_to_form_the_same_automaton_unit_lists
		(allof, regexp, j);
	    else if (allof->mode != rm_nothing)
	      abort ();
	  }
      else if (seq->mode == rm_allof)
	for (k = 0; k < REGEXP_ALLOF (seq)->regexps_num; k++)
	  {
	    unit = REGEXP_ALLOF (seq)->regexps [k];
	    if (unit->mode == rm_unit)
	      process_unit_to_form_the_same_automaton_unit_lists
		(unit, regexp, 0);
	    else if (unit->mode != rm_nothing)
	      abort ();
	  }
      else if (seq->mode == rm_unit)
	process_unit_to_form_the_same_automaton_unit_lists (seq, regexp, 0);
      else if (seq->mode != rm_nothing)
	abort ();
    }
}
