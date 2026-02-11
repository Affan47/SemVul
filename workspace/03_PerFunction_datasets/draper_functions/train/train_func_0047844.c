print_args (boolean ask)
{
  int i;

  for (i = 0; i < bc_state.cmd_argc - 1; i++)
    fprintf (stderr, "%s ", bc_state.cmd_argv[i]);
  if (ask)
    {
      static FILE *tty_stream;
      int c, savec;

      if (!tty_stream)
	{
	  tty_stream = fopen ("/dev/tty", "r");
	  if (!tty_stream)
	    error (1, errno, "/dev/tty");
	}
      fputs ("?...", stderr);
      fflush (stderr);
      c = savec = getc (tty_stream);
      while (c != EOF && c != '\n')
	c = getc (tty_stream);
      if (savec == 'y' || savec == 'Y')
	return true;
    }
  else
    putc ('\n', stderr);

  return false;
}
