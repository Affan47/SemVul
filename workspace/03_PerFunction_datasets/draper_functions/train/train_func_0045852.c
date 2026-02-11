dump_update_ssa (FILE *file)
{
  unsigned i = 0;
  bitmap_iterator bi;

  if (!need_ssa_update_p (cfun))
    return;

  if (new_ssa_names && bitmap_first_set_bit (new_ssa_names) >= 0)
    {
      sbitmap_iterator sbi;

      fprintf (file, "\nSSA replacement table\n");
      fprintf (file, "N_i -> { O_1 ... O_j } means that N_i replaces "
	             "O_1, ..., O_j\n\n");

      EXECUTE_IF_SET_IN_BITMAP (new_ssa_names, 0, i, sbi)
	dump_names_replaced_by (file, ssa_name (i));
    }

  if (symbols_to_rename_set && !bitmap_empty_p (symbols_to_rename_set))
    {
      fprintf (file, "\nSymbols to be put in SSA form\n");
      dump_decl_set (file, symbols_to_rename_set);
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
