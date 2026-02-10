inline_read_summary (void)
{
  struct lto_file_decl_data **file_data_vec = lto_get_file_decl_data ();
  struct lto_file_decl_data *file_data;
  unsigned int j = 0;

  inline_summary_alloc ();

  while ((file_data = file_data_vec[j++]))
    {
      size_t len;
      const char *data = lto_get_section_data (file_data,
					       LTO_section_inline_summary,
					       NULL, &len);
      if (data)
	inline_read_section (file_data, data, len);
      else


	fatal_error ("ipa inline summary is missing in input file");
    }
  if (optimize)
    {
      ipa_register_cgraph_hooks ();
      if (!flag_ipa_cp)
	ipa_prop_read_jump_functions ();
    }
  function_insertion_hook_holder =
    cgraph_add_function_insertion_hook (&add_new_function, NULL);
}
