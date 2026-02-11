free_lang_data (void)
{
  unsigned i;


  if (in_lto_p
      || !flag_generate_lto)
    return 0;


  for (i = 0; i < itk_none; ++i)
    if (integer_types[i])
      TYPE_ALIAS_SET (integer_types[i]) = get_alias_set (integer_types[i]);


  free_lang_data_in_cgraph ();


  ptrdiff_type_node = integer_type_node;
  fileptr_type_node = ptr_type_node;
  if (TREE_CODE (boolean_type_node) != BOOLEAN_TYPE
      || (TYPE_MODE (boolean_type_node)
	  != mode_for_size (BOOL_TYPE_SIZE, MODE_INT, 0))
      || TYPE_PRECISION (boolean_type_node) != 1
      || !TYPE_UNSIGNED (boolean_type_node))
    {
      boolean_type_node = make_unsigned_type (BOOL_TYPE_SIZE);
      TREE_SET_CODE (boolean_type_node, BOOLEAN_TYPE);
      TYPE_MAX_VALUE (boolean_type_node) = build_int_cst (boolean_type_node, 1);
      TYPE_PRECISION (boolean_type_node) = 1;
      boolean_false_node = TYPE_MIN_VALUE (boolean_type_node);
      boolean_true_node = TYPE_MAX_VALUE (boolean_type_node);
    }


  if (TYPE_UNSIGNED (char_type_node))
    unsigned_char_type_node = char_type_node;
  else
    signed_char_type_node = char_type_node;


  lang_hooks.callgraph.analyze_expr = NULL;
  lang_hooks.dwarf_name = lhd_dwarf_name;
  lang_hooks.decl_printable_name = gimple_decl_printable_name;


  diagnostic_starter (global_dc) = default_tree_diagnostic_starter;
  diagnostic_finalizer (global_dc) = default_diagnostic_finalizer;
  diagnostic_format_decoder (global_dc) = default_tree_printer;

  return 0;
}
