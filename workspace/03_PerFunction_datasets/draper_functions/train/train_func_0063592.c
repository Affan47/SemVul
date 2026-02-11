dump_varpool_node (FILE *f, struct varpool_node *node)
{
  dump_symtab_base (f, (symtab_node)node);
  fprintf (f, "  Availability: %s\n",
	   cgraph_function_flags_ready
	   ? cgraph_availability_names[cgraph_variable_initializer_availability (node)]
	   : "not-ready");
  fprintf (f, "  Varpool flags:");
  if (DECL_INITIAL (node->symbol.decl))
    fprintf (f, " initialized");
  if (node->analyzed)
    fprintf (f, " analyzed");
  if (node->finalized)
    fprintf (f, " finalized");
  if (node->output)
    fprintf (f, " output");
  fprintf (f, "\n");
}
