print_idecode_switch_function_header (lf *file,
				      gen_entry *table,
				      int is_function_definition,
				      int nr_prefetched_words)
{
  lf_printf (file, "\n");
  if (options.gen.code == generate_calls)
    {
      lf_printf (file, "static ");
      if (options.gen.icache)
	{
	  lf_printf (file, "idecode_semantic *");
	}
      else
	{
	  lf_printf (file, "unsigned_word");
	}
      if (is_function_definition)
	{
	  lf_printf (file, "\n");
	}
      else
	{
	  lf_printf (file, " ");
	}
      lf_print_table_name (file, table);
      lf_printf (file, "\n(");
      print_icache_function_formal (file, nr_prefetched_words);
      lf_printf (file, ")");
      if (!is_function_definition)
	{
	  lf_printf (file, ";");
	}
      lf_printf (file, "\n");
    }
  if (options.gen.code == generate_jumps && is_function_definition)
    {
      lf_indent (file, -1);
      lf_print_table_name (file, table);
      lf_printf (file, ":\n");
      lf_indent (file, +1);
    }
}
