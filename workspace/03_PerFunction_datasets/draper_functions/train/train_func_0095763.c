help (int argc, char *argv[])
{
  register Command *c;

  if (argc == 1)
    {
      printf ("Commands may be abbreviated.  Commands are:\n\n");
      for (c = cmdtab; c->name; c++)
	if (c->help)
	  {
	    printf ("%-*s\t%s\n", (int) HELPINDENT, c->name, c->help);
	  }
      return 0;
    }
  while (--argc > 0)
    {
      register char *arg;
      arg = *++argv;
      c = getcmd (arg);
      if (Ambiguous (c))
	printf ("?Ambiguous help command %s\n", arg);
      else if (c == (Command *) 0)
	printf ("?Invalid help command %s\n", arg);
      else
	printf ("%s\n", c->help);
    }
  return 0;
}
