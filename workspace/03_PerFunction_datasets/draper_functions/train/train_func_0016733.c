dump_incr_vec (void)
{
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      unsigned i;

      fprintf (dump_file, "\nIncrement vector:\n\n");

      for (i = 0; i < incr_vec_len; i++)
	{
	  fprintf (dump_file, "%3d  increment:   ", i);
	  dump_double_int (dump_file, incr_vec[i].incr, false);
	  fprintf (dump_file, "\n     count:       %d", incr_vec[i].count);
	  fprintf (dump_file, "\n     cost:        %d", incr_vec[i].cost);
	  fputs ("\n     initializer: ", dump_file);
	  print_generic_expr (dump_file, incr_vec[i].initializer, 0);
	  fputs ("\n\n", dump_file);
	}
    }
}
