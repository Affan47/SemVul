sendcmd (int argc, char **argv)
{
  int count;
  int i;
  struct sendlist *s;
  int success = 0;
  int needconnect = 0;

  if (argc < 2)
    {
      printf ("need at least one argument for 'send' command\n");
      printf ("'send ?' for help\n");
      return 0;
    }


  count = 0;
  for (i = 1; i < argc; i++)
    {
      s = GETSEND (argv[i]);
      if (s == 0)
	{
	  printf ("Unknown send argument '%s'\n'send ?' for help.\n",
		  argv[i]);
	  return 0;
	}
      else if (Ambiguous (s))
	{
	  printf ("Ambiguous send argument '%s'\n'send ?' for help.\n",
		  argv[i]);
	  return 0;
	}
      if (i + s->narg >= argc)
	{
	  fprintf (stderr,
		   "Need %d argument%s to 'send %s' command.  'send %s ?' for help.\n",
		   s->narg, s->narg == 1 ? "" : "s", s->name, s->name);
	  return 0;
	}
      count += s->nbyte;
      if (s->handler == send_help)
	{
	  send_help ();
	  return 0;
	}

      i += s->narg;
      needconnect += s->needconnect;
    }
  if (!connected && needconnect)
    {
      printf ("?Need to be connected first.\n");
      printf ("'send ?' for help\n");
      return 0;
    }

  if (NETROOM () < count)
    {
      printf ("There is not enough room in the buffer TO the network\n");
      printf ("to process your request.  Nothing will be done.\n");
      printf ("('send synch' will throw away most data in the network\n");
      printf ("buffer, if this might help.)\n");
      return 0;
    }

  count = 0;
  for (i = 1; i < argc; i++)
    {
      if ((s = GETSEND (argv[i])) == 0)
	{
	  fprintf (stderr, "Telnet 'send' error - argument disappeared!\n");
	  quit ();
	}
      if (s->handler)
	{
	  count++;
	  success += (*s->handler) ((s->narg > 0) ? argv[i + 1] : 0,
				    (s->narg > 1) ? argv[i + 2] : 0);
	  i += s->narg;
	}
      else
	{
	  NET2ADD (IAC, s->what);
	  printoption ("SENT", IAC, s->what);
	}
    }
  return (count == success);
}
