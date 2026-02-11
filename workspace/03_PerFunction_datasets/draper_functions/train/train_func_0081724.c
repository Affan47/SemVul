print_icache_function_type (lf *file)
{
  int nr;
  if (options.gen.semantic_icache)
    {
      nr = print_semantic_function_type (file);
    }
  else
    {
      nr = lf_printf (file, "%sidecode_semantic *",
		      options.module.global.prefix.l);
    }
  return nr;
}
