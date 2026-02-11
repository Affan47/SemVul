c_genericize (tree fndecl)
{
  FILE *dump_orig;
  int local_dump_flags;
  struct cgraph_node *cgn;


  dump_orig = dump_begin (TDI_original, &local_dump_flags);
  if (dump_orig)
    {
      fprintf (dump_orig, "\n;; Function %s",
	       lang_hooks.decl_printable_name (fndecl, 2));
      fprintf (dump_orig, " (%s)\n",
	       (!DECL_ASSEMBLER_NAME_SET_P (fndecl) ? "null"
		: IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (fndecl))));
      fprintf (dump_orig, ";; enabled by -%s\n", dump_flag_name (TDI_original));
      fprintf (dump_orig, "\n");

      if (local_dump_flags & TDF_RAW)
	dump_node (DECL_SAVED_TREE (fndecl),
		   TDF_SLIM | local_dump_flags, dump_orig);
      else
	print_c_tree (dump_orig, DECL_SAVED_TREE (fndecl));
      fprintf (dump_orig, "\n");

      dump_end (TDI_original, dump_orig);
    }


  cgn = cgraph_get_create_node (fndecl);
  for (cgn = cgn->nested; cgn ; cgn = cgn->next_nested)
    c_genericize (cgn->symbol.decl);
}
