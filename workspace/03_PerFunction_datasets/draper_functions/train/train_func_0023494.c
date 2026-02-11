solution_set_expand (bitmap result, bitmap set)
{
  bitmap_iterator bi;
  bitmap vars = NULL;
  unsigned j;


  EXECUTE_IF_SET_IN_BITMAP (set, 0, j, bi)
    {
      varinfo_t v = get_varinfo (j);
      if (v->is_artificial_var
	  || v->is_full_var)
	continue;
      v = lookup_vi_for_tree (v->decl);
      if (vars == NULL)
	vars = BITMAP_ALLOC (NULL);
      bitmap_set_bit (vars, v->id);
    }


  if (vars != NULL)
    {
      EXECUTE_IF_SET_IN_BITMAP (vars, 0, j, bi)
	{
	  varinfo_t v = get_varinfo (j);
	  for (; v != NULL; v = v->next)
	    bitmap_set_bit (result, v->id);
	}
      BITMAP_FREE (vars);
    }
}
