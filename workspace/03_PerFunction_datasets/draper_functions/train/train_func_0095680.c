encrypt_cmd (int argc, char *argv[])
{
  struct encryptlist *c;

  if (argc < 2)
    {
      fprintf (stderr,
	       "Need an argument to 'encrypt' command.  'encrypt ?' for help.\n");
      return 0;
    }

  c = (struct encryptlist *)
    genget (argv[1], (char **) EncryptList, sizeof (struct encryptlist));
  if (c == 0)
    {
      fprintf (stderr, "'%s': unknown argument ('encrypt ?' for help).\n",
	       argv[1]);
      return 0;
    }
  if (Ambiguous (c))
    {
      fprintf (stderr, "'%s': ambiguous argument ('encrypt ?' for help).\n",
	       argv[1]);
      return 0;
    }
  argc -= 2;
  if (argc < c->minarg || argc > c->maxarg)
    {
      if (c->minarg == c->maxarg)
	{
	  fprintf (stderr, "Need %s%d argument%s ",
		   c->minarg < argc ? "only " : "", c->minarg,
		   c->minarg == 1 ? "" : "s");
	}
      else
	{
	  fprintf (stderr, "Need %s%d-%d arguments ",
		   c->maxarg < argc ? "only " : "", c->minarg, c->maxarg);
	}
      fprintf (stderr, "to 'encrypt %s' command.  'encrypt ?' for help.\n",
	       c->name);
      return 0;
    }
  if (c->needconnect && !connected)
    {
      if (!(argc && (isprefix (argv[2], "help") || isprefix (argv[2], "?"))))
	{
	  printf ("?Need to be connected first.\n");
	  return 0;
	}
    }
  return ((*c->handler) (argc > 0 ? argv[2] : 0,
			 argc > 1 ? argv[3] : 0, argc > 2 ? argv[4] : 0));
}
