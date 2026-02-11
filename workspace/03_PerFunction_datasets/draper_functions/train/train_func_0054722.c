print_direction_vector (FILE *outf,
			lambda_vector dirv,
			int length)
{
  int eq;

  for (eq = 0; eq < length; eq++)
    {
      enum data_dependence_direction dir = ((enum data_dependence_direction)
					    dirv[eq]);

      switch (dir)
	{
	case dir_positive:
	  fprintf (outf, "    +");
	  break;
	case dir_negative:
	  fprintf (outf, "    -");
	  break;
	case dir_equal:
	  fprintf (outf, "    =");
	  break;
	case dir_positive_or_equal:
	  fprintf (outf, "   +=");
	  break;
	case dir_positive_or_negative:
	  fprintf (outf, "   +-");
	  break;
	case dir_negative_or_equal:
	  fprintf (outf, "   -=");
	  break;
	case dir_star:
	  fprintf (outf, "    *");
	  break;
	default:
	  fprintf (outf, "indep");
	  break;
	}
    }
  fprintf (outf, "\n");
}
