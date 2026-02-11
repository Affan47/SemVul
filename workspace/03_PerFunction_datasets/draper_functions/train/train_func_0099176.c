dump_update_ssa (FILE *file)
{
  unsigned i = 0;
  bitmap_iterator bi;

  if (!need_ssa_update_p (cfun))
    return;

  if (new_ssa_names && sbitmap_first_set_bit (new_ssa_names) >= 0)
    {
      sbitmap_iterator sbi;

      fprintf (file, "\nSSA replacement table\n");
      fprintf (file, "N_i -> { O_1 ... O_j } means that N_i replaces "
	             "O_1, ..., O_j\n\n");

      EXECUTE_IF_SET_IN_SBITMAP (new_ssa_names, 0, i, sbi)
	dump_names_replaced_by (file, ssa_name (i));

      fprintf (file, "\n");
      fprintf (file, "Number of virtual NEW -> OLD mappings: %7u\n",
	       update_ssa_stats.num_virtual_mappings);
      fprintf (file, "Number of real NEW -> OLD mappings:    %7u\n",
	       update_ssa_stats.num_total_mappings
	       - update_ssa_stats.num_virtual_mappings);
      fprintf (file, "Number of total NEW -> OLD mappings:   %7u\n",
	       update_ssa_stats.num_total_mappings);

      fprintf (file, "\nNumber of virtual symbols: %u\n",
	       update_ssa_stats.num_virtual_symbols);
    }

  if (!bitmap_empty_p (SYMS_TO_RENAME (cfun)))
    {
      fprintf (file, "\nSymbols to be put in SSA form\n");
      dump_decl_set (file, SYMS_TO_RENAME (cfun));
      fprintf (file, "\n");
    }

  if (names_to_release && !bitmap_empty_p (names_to_release))
    {
      fprintf (file, "\nSSA names to release after updating the SSA web\n\n");
      EXECUTE_IF_SET_IN_BITMAP (names_to_release, 0, i, bi)
	{
	  print_generic_expr (file, ssa_name (i), 0);
	  fprintf (file, " ");
	}
      fprintf (file, "\n");
    }
}
