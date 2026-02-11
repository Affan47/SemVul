modehelp (void)
{
  struct modelist *mt;

  printf ("format is:  'mode Mode', where 'Mode' is one of:\n\n");
  for (mt = ModeList; mt->name; mt++)
    {
      if (mt->help)
	{
	  if (*mt->help)
	    printf ("%-15s %s\n", mt->name, mt->help);
	  else
	    printf ("\n");
	}
    }
  return 0;
}
