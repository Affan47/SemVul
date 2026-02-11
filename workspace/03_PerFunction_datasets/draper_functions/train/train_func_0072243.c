print_icache_internal_function_declaration (lf *file,
					    function_entry * function,
					    void *data)
{
  ASSERT (options.gen.icache);
  if (function->is_internal)
    {
      lf_printf (file, "\n");
      lf_print__function_type_function (file, print_icache_function_type,
					"INLINE_ICACHE", "\n");
      print_function_name (file,
			   function->name,
			   NULL, NULL, NULL, function_name_prefix_icache);
      lf_printf (file, "\n(");
      print_icache_function_formal (file, 0);
      lf_printf (file, ");\n");
    }
}
