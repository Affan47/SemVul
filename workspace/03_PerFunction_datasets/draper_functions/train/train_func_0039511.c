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


  lang_hooks.callgraph.analyze_expr = NULL;
  lang_hooks.dwarf_name = lhd_dwarf_name;
  lang_hooks.decl_printable_name = gimple_decl_printable_name;


  diagnostic_starter (global_dc) = default_tree_diagnostic_starter;
  diagnostic_finalizer (global_dc) = default_diagnostic_finalizer;
  diagnostic_format_decoder (global_dc) = default_tree_printer;

  return 0;
}
