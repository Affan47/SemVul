parse_vector (const SANE_Option_Descriptor * opt, const char *str,
	      SANE_Word * vector, size_t vector_length)
{
  SANE_Word value, prev_value = 0;
  int index = -1, prev_index = 0;
  char *end, separator = '\0';


  memset (vector, 0, vector_length * sizeof (SANE_Word));

  do
    {
      if (*str == '[')
	{

	  index = strtol (++str, &end, 10);
	  if (str == end || *end != ']')
	    {
	      fprintf (stderr, "%s: option --%s: closing bracket missing "
		       "(rest of option: %s)\n", prog_name, opt->name, str);
	      exit (1);
	    }
	  str = end + 1;
	}
      else
	++index;

      if (index < 0 || index >= (int) vector_length)
	{
	  fprintf (stderr,
		   "%s: option --%s: index %d out of range [0..%ld]\n",
		   prog_name, opt->name, index, (long) vector_length - 1);
	  exit (1);
	}


      str = parse_scalar (opt, str, &value);
      if (!str)
	exit (1);

      if (*str && *str != '-' && *str != ',')
	{
	  fprintf (stderr,
		   "%s: option --%s: illegal separator (rest of option: %s)\n",
		   prog_name, opt->name, str);
	  exit (1);
	}


      vector[index] = value;
      if (separator == '-')
	{

	  double v, slope;
	  int i;

	  v = (double) prev_value;
	  slope = ((double) value - v) / (index - prev_index);

	  for (i = prev_index + 1; i < index; ++i)
	    {
	      v += slope;
	      vector[i] = (SANE_Word) v;
	    }
	}

      prev_index = index;
      prev_value = value;
      separator = *str++;
    }
  while (separator == ',' || separator == '-');

  if (verbose > 2)
    {
      int i;

      fprintf (stderr, "%s: value for --%s is: ", prog_name, opt->name);
      for (i = 0; i < (int) vector_length; ++i)
	if (opt->type == SANE_TYPE_FIXED)
	  fprintf (stderr, "%g ", SANE_UNFIX (vector[i]));
	else
	  fprintf (stderr, "%d ", vector[i]);
      fputc ('\n', stderr);
    }
}
