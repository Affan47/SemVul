clear_tag_tab ()
{
  int             i;

  if (! tagtab || tagtab->scope_level < scope_level)
    return;

  for (i = 0; i < SIZE_HAS_LOC; i++)
    {
      if (NULL != tagtab->hastab_loc[i].name)
	{
#if 0
	  free (tagtab->hastab_loc[i].name);
#endif
	  tagtab->hastab_loc[i].name = NULL;
	  clear_internal_type ((tagtab->table +
				tagtab->hastab_loc[i].def)->type);
	  tagtab->hastab_loc[i].def = 0;
	  tagtab->hastab_loc[i].count = 0;
	  tagtab->hastab_loc[i].use_line_number = 0;
	  tagtab->hastab_loc[i].l_value_flag = 0;
	  if (NULL != tagtab->hastab_loc[i].next)
	    clear_hash_tab_next (tagtab, tagtab->hastab_loc[i].next);
	}
    }
  tagtab->pi_loc = 0;
  tagtab = tagtab->previous_level;

  return;
}
