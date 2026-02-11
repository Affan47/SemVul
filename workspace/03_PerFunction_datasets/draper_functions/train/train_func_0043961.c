d_print_array_type (dpi, dc, mods)
     struct d_print_info *dpi;
     const struct demangle_component *dc;
     struct d_print_mod *mods;
{
  int need_space;

  need_space = 1;
  if (mods != NULL)
    {
      int need_paren;
      struct d_print_mod *p;

      need_paren = 0;
      for (p = mods; p != NULL; p = p->next)
	{
	  if (! p->printed)
	    {
	      if (p->mod->type == DEMANGLE_COMPONENT_ARRAY_TYPE)
		{
		  need_space = 0;
		  break;
		}
	      else
		{
		  need_paren = 1;
		  need_space = 1;
		  break;
		}
	    }
	}

      if (need_paren)
	d_append_string_constant (dpi, " (");

      d_print_mod_list (dpi, mods, 0);

      if (need_paren)
	d_append_char (dpi, ')');
    }

  if (need_space)
    d_append_char (dpi, ' ');

  d_append_char (dpi, '[');

  if (d_left (dc) != NULL)
    d_print_comp (dpi, d_left (dc));

  d_append_char (dpi, ']');
}
