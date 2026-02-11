create_variable_info_for_1 (tree decl, const char *name)
{
  varinfo_t vi, newvi;
  tree decl_type = TREE_TYPE (decl);
  tree declsize = DECL_P (decl) ? DECL_SIZE (decl) : TYPE_SIZE (decl_type);
  vec<fieldoff_s> fieldstack = vNULL;
  fieldoff_s *fo;
  unsigned int i;

  if (!declsize
      || !host_integerp (declsize, 1))
    {
      vi = new_var_info (decl, name);
      vi->offset = 0;
      vi->size = ~0;
      vi->fullsize = ~0;
      vi->is_unknown_size_var = true;
      vi->is_full_var = true;
      vi->may_have_pointers = true;
      return vi;
    }


  if (use_field_sensitive
      && var_can_have_subvars (decl)


      && !(in_ipa_mode
	   && is_global_var (decl)
	   && DECL_INITIAL (decl)))
    {
      fieldoff_s *fo = NULL;
      bool notokay = false;
      unsigned int i;

      push_fields_onto_fieldstack (decl_type, &fieldstack, 0);

      for (i = 0; !notokay && fieldstack.iterate (i, &fo); i++)
	if (fo->has_unknown_size
	    || fo->offset < 0)
	  {
	    notokay = true;
	    break;
	  }


      if (!notokay)
	{
	  sort_fieldstack (fieldstack);


	  notokay = check_for_overlaps (fieldstack);
	}

      if (notokay)
	fieldstack.release ();
    }


  if (fieldstack.length () <= 1
      || fieldstack.length () > MAX_FIELDS_FOR_FIELD_SENSITIVE)
    {
      vi = new_var_info (decl, name);
      vi->offset = 0;
      vi->may_have_pointers = true;
      vi->fullsize = TREE_INT_CST_LOW (declsize);
      vi->size = vi->fullsize;
      vi->is_full_var = true;
      fieldstack.release ();
      return vi;
    }

  vi = new_var_info (decl, name);
  vi->fullsize = TREE_INT_CST_LOW (declsize);
  for (i = 0, newvi = vi;
       fieldstack.iterate (i, &fo);
       ++i, newvi = newvi->next)
    {
      const char *newname = "NULL";
      char *tempname;

      if (dump_file)
	{
	  asprintf (&tempname, "%s." HOST_WIDE_INT_PRINT_DEC
		    "+" HOST_WIDE_INT_PRINT_DEC, name, fo->offset, fo->size);
	  newname = ggc_strdup (tempname);
	  free (tempname);
	}
      newvi->name = newname;
      newvi->offset = fo->offset;
      newvi->size = fo->size;
      newvi->fullsize = vi->fullsize;
      newvi->may_have_pointers = fo->may_have_pointers;
      newvi->only_restrict_pointers = fo->only_restrict_pointers;
      if (i + 1 < fieldstack.length ())
	newvi->next = new_var_info (decl, name);
    }

  fieldstack.release ();

  return vi;
}
