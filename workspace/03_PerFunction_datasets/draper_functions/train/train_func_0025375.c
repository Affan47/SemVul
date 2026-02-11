process_presence_absence_patterns (char ***patterns, int num,
				   pos_t req_pos ATTRIBUTE_UNUSED,
				   int presence_p, int final_p)
{
  pattern_set_el_t el_list;
  pattern_set_el_t last_el;
  pattern_set_el_t new_el;
  decl_t decl_in_table;
  int i, j;

  el_list = NULL;
  last_el = NULL;
  for (i = 0; i < num; i++)
    {
      for (j = 0; patterns [i] [j] != NULL; j++)
	;
      new_el = XCREATENODEVAR (struct pattern_set_el,
			       sizeof (struct pattern_set_el)
			       + sizeof (struct unit_decl *) * j);
      new_el->unit_decls
	= (struct unit_decl **) ((char *) new_el
				 + sizeof (struct pattern_set_el));
      new_el->next_pattern_set_el = NULL;
      if (last_el == NULL)
	el_list = last_el = new_el;
      else
	{
	  last_el->next_pattern_set_el = new_el;
	  last_el = last_el->next_pattern_set_el;
	}
      new_el->units_num = 0;
      for (j = 0; patterns [i] [j] != NULL; j++)
	{
	  decl_in_table = find_decl (patterns [i] [j]);
	  if (decl_in_table == NULL)
	    error ((presence_p
		    ? (final_p
		       ? "unit `%s' in final presence set is not declared"
		       : "unit `%s' in presence set is not declared")
		    : (final_p
		       ? "unit `%s' in final absence set is not declared"
		       : "unit `%s' in absence set is not declared")),
		   patterns [i] [j]);
	  else if (decl_in_table->mode != dm_unit)
	    error ((presence_p
		    ? (final_p
		       ? "`%s' in final presence set is not unit"
		       : "`%s' in presence set is not unit")
		    : (final_p
		       ? "`%s' in final absence set is not unit"
		       : "`%s' in absence set is not unit")),
		   patterns [i] [j]);
	  else
	    {
	      new_el->unit_decls [new_el->units_num]
		= DECL_UNIT (decl_in_table);
	      new_el->units_num++;
	    }
	}
    }
  return el_list;
}
