process_regexp (regexp)
     regexp_t regexp;
{
  decl_t decl_in_table;
  regexp_t new_regexp;
  int i;

  if (regexp->mode == rm_unit)
    {
      decl_in_table = find_decl (REGEXP_UNIT (regexp)->name);
      if (decl_in_table == NULL)
        error ("undeclared unit or reservation `%s'",
	       REGEXP_UNIT (regexp)->name);
      else if (decl_in_table->mode == dm_unit)
	{
	  DECL_UNIT (decl_in_table)->unit_is_used = 1;
	  REGEXP_UNIT (regexp)->unit_decl = DECL_UNIT (decl_in_table);
	}
      else if (decl_in_table->mode == dm_reserv)
	{
	  DECL_RESERV (decl_in_table)->reserv_is_used = 1;
	  new_regexp = create_node (sizeof (struct regexp));
	  new_regexp->mode = rm_reserv;
	  new_regexp->pos = regexp->pos;
	  REGEXP_RESERV (new_regexp)->name = REGEXP_UNIT (regexp)->name;
	  REGEXP_RESERV (new_regexp)->reserv_decl
	    = DECL_RESERV (decl_in_table);
	  regexp = new_regexp;
	}
      else
	abort ();
    }
  else if (regexp->mode == rm_sequence)
    for (i = 0; i <REGEXP_SEQUENCE (regexp)->regexps_num; i++)
     REGEXP_SEQUENCE (regexp)->regexps [i]
	= process_regexp (REGEXP_SEQUENCE (regexp)->regexps [i]);
  else if (regexp->mode == rm_allof)
    for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
      REGEXP_ALLOF (regexp)->regexps [i]
        = process_regexp (REGEXP_ALLOF (regexp)->regexps [i]);
  else if (regexp->mode == rm_oneof)
    for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
      REGEXP_ONEOF (regexp)->regexps [i]
	= process_regexp (REGEXP_ONEOF (regexp)->regexps [i]);
  else if (regexp->mode == rm_repeat)
    REGEXP_REPEAT (regexp)->regexp
      = process_regexp (REGEXP_REPEAT (regexp)->regexp);
  else if (regexp->mode != rm_nothing)
    abort ();
  return regexp;
}
