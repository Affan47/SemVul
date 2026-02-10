s_macro (int ignore ATTRIBUTE_UNUSED)
{
  char *file, *eol;
  unsigned int line;
  sb s;
  const char *err;
  const char *name;

  as_where (&file, &line);

  eol = find_end_of_line (input_line_pointer, 0);
  sb_build (&s, eol - input_line_pointer);
  sb_add_buffer (&s, input_line_pointer, eol - input_line_pointer);
  input_line_pointer = eol;

  if (line_label != NULL)
    {
      sb label;
      size_t len;

      name = S_GET_NAME (line_label);
      len = strlen (name);
      sb_build (&label, len);
      sb_add_buffer (&label, name, len);
      err = define_macro (0, &s, &label, get_macro_line_sb, file, line, &name);
      sb_kill (&label);
    }
  else
    err = define_macro (0, &s, NULL, get_macro_line_sb, file, line, &name);
  if (err != NULL)
    as_bad_where (file, line, err, name);
  else
    {
      if (line_label != NULL)
	{
	  S_SET_SEGMENT (line_label, absolute_section);
	  S_SET_VALUE (line_label, 0);
	  symbol_set_frag (line_label, &zero_address_frag);
	}

      if (((NO_PSEUDO_DOT || flag_m68k_mri)
	   && hash_find (po_hash, name) != NULL)
	  || (!flag_m68k_mri
	      && *name == '.'
	      && hash_find (po_hash, name + 1) != NULL))
	as_warn_where (file,
		 line,
		 _("attempt to redefine pseudo-op `%s' ignored"),
		 name);
    }

  sb_kill (&s);
}
