obj_elf_vtable_inherit (int ignore ATTRIBUTE_UNUSED)
{
  char *cname, *pname;
  symbolS *csym, *psym;
  char c, bad = 0;

  if (*input_line_pointer == '#')
    ++input_line_pointer;

  cname = input_line_pointer;
  c = get_symbol_end ();
  csym = symbol_find (cname);


  if (csym == NULL || symbol_get_frag (csym) == NULL)
    {
      as_bad (_("expected `%s' to have already been set for .vtable_inherit"),
	      cname);
      bad = 1;
    }

  *input_line_pointer = c;

  SKIP_WHITESPACE ();
  if (*input_line_pointer != ',')
    {
      as_bad (_("expected comma after name in .vtable_inherit"));
      ignore_rest_of_line ();
      return NULL;
    }

  ++input_line_pointer;
  SKIP_WHITESPACE ();

  if (*input_line_pointer == '#')
    ++input_line_pointer;

  if (input_line_pointer[0] == '0'
      && (input_line_pointer[1] == '\0'
	  || ISSPACE (input_line_pointer[1])))
    {
      psym = section_symbol (absolute_section);
      ++input_line_pointer;
    }
  else
    {
      pname = input_line_pointer;
      c = get_symbol_end ();
      psym = symbol_find_or_make (pname);
      *input_line_pointer = c;
    }

  demand_empty_rest_of_line ();

  if (bad)
    return NULL;

  gas_assert (symbol_get_value_expression (csym)->X_op == O_constant);
  return fix_new (symbol_get_frag (csym),
		  symbol_get_value_expression (csym)->X_add_number,
		  0, psym, 0, 0, BFD_RELOC_VTABLE_INHERIT);
}
