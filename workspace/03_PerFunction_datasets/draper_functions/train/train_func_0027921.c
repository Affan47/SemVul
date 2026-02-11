gather_chrec_stats (tree chrec, struct chrec_stats *stats)
{
  if (dump_file && (dump_flags & TDF_STATS))
    {
      fprintf (dump_file, "(classify_chrec ");
      print_generic_expr (dump_file, chrec, 0);
      fprintf (dump_file, "\n");
    }

  stats->nb_chrecs++;

  if (chrec == NULL_TREE)
    {
      stats->nb_undetermined++;
      return;
    }

  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      if (evolution_function_is_affine_p (chrec))
	{
	  if (dump_file && (dump_flags & TDF_STATS))
	    fprintf (dump_file, "  affine_univariate\n");
	  stats->nb_affine++;
	}
      else if (evolution_function_is_affine_multivariate_p (chrec, 0))
	{
	  if (dump_file && (dump_flags & TDF_STATS))
	    fprintf (dump_file, "  affine_multivariate\n");
	  stats->nb_affine_multivar++;
	}
      else
	{
	  if (dump_file && (dump_flags & TDF_STATS))
	    fprintf (dump_file, "  higher_degree_polynomial\n");
	  stats->nb_higher_poly++;
	}

      break;

    default:
      break;
    }

  if (chrec_contains_undetermined (chrec))
    {
      if (dump_file && (dump_flags & TDF_STATS))
	fprintf (dump_file, "  undetermined\n");
      stats->nb_undetermined++;
    }

  if (dump_file && (dump_flags & TDF_STATS))
    fprintf (dump_file, ")\n");
}
