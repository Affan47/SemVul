restore_vars_to_original_value (void)
{
  while (VEC_length (tree, const_and_copies_stack) > 0)
    {
      tree prev_value, dest;

      dest = VEC_pop (tree, const_and_copies_stack);

      if (dest == NULL)
	break;

      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "<<<< COPY ");
	  print_generic_expr (dump_file, dest, 0);
	  fprintf (dump_file, " = ");
	  print_generic_expr (dump_file, SSA_NAME_VALUE (dest), 0);
	  fprintf (dump_file, "\n");
	}

      prev_value = VEC_pop (tree, const_and_copies_stack);
      set_ssa_name_value (dest, prev_value);
    }
}
