dump_stack_var_partition (void)
{
  size_t si, i, j, n = stack_vars_num;

  for (si = 0; si < n; ++si)
    {
      i = stack_vars_sorted[si];


      if (stack_vars[i].representative != i)
	continue;

      fprintf (dump_file, "Partition %lu: size " HOST_WIDE_INT_PRINT_DEC
	       " align %u\n", (unsigned long) i, stack_vars[i].size,
	       stack_vars[i].alignb);

      for (j = i; j != EOC; j = stack_vars[j].next)
	{
	  fputc ('\t', dump_file);
	  print_generic_expr (dump_file, stack_vars[j].decl, dump_flags);
	}
      fputc ('\n', dump_file);
    }
}
