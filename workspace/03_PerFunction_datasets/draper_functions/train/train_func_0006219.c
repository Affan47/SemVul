cp_debug_print_unparsed_queues (FILE *file,
				vec<cp_unparsed_functions_entry, va_gc> *s)
{
  unsigned i;
  cp_unparsed_functions_entry *uf;

  fprintf (file, "Unparsed functions\n");
  for (i = 0; vec_safe_iterate (s, i, &uf); i++)
    {
      fprintf (file, "#%u:\n", i);
      cp_debug_print_unparsed_function (file, uf);
    }
}
