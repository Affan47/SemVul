argcv_free (int argc, char **argv)
{
  if (!argv)
    return 0;
  if (argc > 0)
    {
      while (--argc >= 0)
	if (argv[argc])
	  free (argv[argc]);
    }
  else
    {
      int i;
      for (i = 0; argv[i]; i++)
	free (argv[i]);
    }
  free (argv);
  return 0;
}
