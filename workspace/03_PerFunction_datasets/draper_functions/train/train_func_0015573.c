init_dynamic_asm_fprintf_info (void)
{
  static tree hwi;

  if (!hwi)
    {
      format_length_info *new_asm_fprintf_length_specs;
      unsigned int i;


      hwi = maybe_get_identifier ("__gcc_host_wide_int__");
      if (!hwi)
	{
	  error ("'__gcc_host_wide_int__' is not defined as a type");
	  return;
	}
      hwi = identifier_global_value (hwi);
      if (!hwi || TREE_CODE (hwi) != TYPE_DECL)
	{
	  error ("'__gcc_host_wide_int__' is not defined as a type");
	  return;
	}
      hwi = DECL_ORIGINAL_TYPE (hwi);
      if (!hwi)
	abort ();
      if (hwi != long_integer_type_node && hwi != long_long_integer_type_node)
	{
	  error ("'__gcc_host_wide_int__' is not defined as 'long'"
		 " or 'long long'");
	  return;
	}


      new_asm_fprintf_length_specs = xmemdup (asm_fprintf_length_specs,
					      sizeof (asm_fprintf_length_specs),
					      sizeof (asm_fprintf_length_specs));


      i = find_length_info_modifier_index (new_asm_fprintf_length_specs, 'w');
      if (hwi == long_integer_type_node)
	new_asm_fprintf_length_specs[i].index = FMT_LEN_l;
      else if (hwi == long_long_integer_type_node)
	new_asm_fprintf_length_specs[i].index = FMT_LEN_ll;
      else
	abort ();


      dynamic_format_types[asm_fprintf_format_type].length_char_specs =
	new_asm_fprintf_length_specs;
    }
}
