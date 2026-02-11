prep_child_for_exec (void)
{
  if (!keep_stdin)
    {
      const char inputfile[] = "/dev/null";


      close(0);
      if (open(inputfile, O_RDONLY) < 0)
	{


	  error (0, errno, "%s", quotearg_n_style(0, locale_quoting_style, inputfile));
	}
    }
}
