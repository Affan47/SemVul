read_args(int argc, char *argv[])
{
  int n;
  char c = 'i';
  int used = 1;


  for (n = 1; n < argc; n++)
  {

    if ((argv[n][0] == '-' || argv[n][0] == '+') && argv[n][1])
    {

      if (!used)
	if (mlevel(3))
	  fprintf(stderr, "Warning: option '-%c' not used.\n", c);


      c = tolower(argv[n][1]);


      used = arg_start(c);


      if (argv[n][2])
      {

	if (used < 2)
	  used = arg_input(c, argv[n] + 2);

	else if (mlevel(2) && used == 2)
	{
	  fprintf(stderr, "Warning: option '-%c' has an attached argument (ignored).\n", c);
	  used = 3;
	}
      }
    }

    else
    {

      if (used < 2)
	used = arg_input(c, argv[n]);

      else if (mlevel(2) && used == 2)
      {
	fprintf(stderr, "Warning: option '-%c' has too many arguments (ignored).\n", c);
	used = 3;
      }
    }
  }


  if (!used)
    if (mlevel(3))
      fprintf(stderr, "Warning: option '-%c' not used.\n", c);
}
