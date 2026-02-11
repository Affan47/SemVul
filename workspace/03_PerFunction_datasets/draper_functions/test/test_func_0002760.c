clear_hash_tab ()
{
  int             i;

  if (!identtab_loc || identtab_loc->scope_level < scope_level)
    return;

  for (i = 0; i < SIZE_HAS_LOC; i++)
    {
      if (NULL != identtab_loc->hastab_loc[i].name)
	{
	  if (!identtab_loc->hastab_loc[i].count)
	    {
	      text = identtab_loc->hastab_loc[i].name;
	      error_message (6003);
	    }
	  if ((0 == identtab_loc->hastab_loc[i].l_value_flag) &&
	      (0 != identtab_loc->hastab_loc[i].count))
	    {
	      text = identtab_loc->hastab_loc[i].name;
	      error_message (6006);
	    }
#if 0
	  free (identtab_loc->hastab_loc[i].name);
#endif
	  identtab_loc->hastab_loc[i].name = NULL;
	  clear_internal_type ((identtab_loc->table +
				identtab_loc->hastab_loc[i].def)->type);
	  identtab_loc->hastab_loc[i].def = 0;
	  identtab_loc->hastab_loc[i].count = 0;
	  identtab_loc->hastab_loc[i].use_line_number = 0;
	  identtab_loc->hastab_loc[i].l_value_flag = 0;
	  if (NULL != identtab_loc->hastab_loc[i].next)
	    clear_hash_tab_next (identtab_loc,
				 identtab_loc->hastab_loc[i].next);
	}
    }
  identtab_loc->pi_loc = 0;
  identtab_loc = identtab_loc->previous_level;

  return;
}
