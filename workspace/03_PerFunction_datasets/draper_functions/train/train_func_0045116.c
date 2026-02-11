process_regexp_cycles (regexp, start_cycle)
     regexp_t regexp;
     int start_cycle;
{
  int i;

  if (regexp->mode == rm_unit)
    {
      if (REGEXP_UNIT (regexp)->unit_decl->max_occ_cycle_num < start_cycle)
	REGEXP_UNIT (regexp)->unit_decl->max_occ_cycle_num = start_cycle;
      return start_cycle;
    }
  else if (regexp->mode == rm_reserv)
    return process_regexp_cycles (REGEXP_RESERV (regexp)->reserv_decl->regexp,
                                  start_cycle);
  else if (regexp->mode == rm_repeat)
    {
      for (i = 0; i < REGEXP_REPEAT (regexp)->repeat_num; i++)
        start_cycle = process_regexp_cycles (REGEXP_REPEAT (regexp)->regexp,
					     start_cycle) + 1;
      return start_cycle;
    }
  else if (regexp->mode == rm_sequence)
    {
      for (i = 0; i <REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	start_cycle
          = process_regexp_cycles (REGEXP_SEQUENCE (regexp)->regexps [i],
				   start_cycle) + 1;
      return start_cycle;
    }
  else if (regexp->mode == rm_allof)
    {
      int finish_cycle = 0;
      int cycle;

      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	{
	  cycle = process_regexp_cycles (REGEXP_ALLOF (regexp)->regexps [i],
					 start_cycle);
	  if (finish_cycle < cycle)
	    finish_cycle = cycle;
	}
      return finish_cycle;
    }
  else if (regexp->mode == rm_oneof)
    {
      int finish_cycle = 0;
      int cycle;

      for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	{
	  cycle = process_regexp_cycles (REGEXP_ONEOF (regexp)->regexps [i],
					 start_cycle);
	  if (finish_cycle < cycle)
	    finish_cycle = cycle;
	}
      return finish_cycle;
    }
  else
    {
      if (regexp->mode != rm_nothing)
	abort ();
      return start_cycle;
    }
}
