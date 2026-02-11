exchange (argv)
     char **argv;
{
  int bottom = first_nonopt;
  int middle = last_nonopt;
  int top = optind;
  char *tem;


  while (top > middle && middle > bottom)
    {
      if (top - middle > middle - bottom)
	{

	  int len = middle - bottom;
	  register int i;


	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[top - (middle - bottom) + i];
	      argv[top - (middle - bottom) + i] = tem;
	    }

	  top -= len;
	}
      else
	{

	  int len = top - middle;
	  register int i;


	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[middle + i];
	      argv[middle + i] = tem;
	    }

	  bottom += len;
	}
    }


  first_nonopt += (optind - last_nonopt);
  last_nonopt = optind;
}
