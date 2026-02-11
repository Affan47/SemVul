_tourneyprint (parse_t parse, int clevel, int cevent)
{
  char *mytok;
  int toknr;
  tourneyindex_t ti;

  toknr = 0;
  ti.taction = A_PRINT;
  _tourneysetsection (&ti, clevel);

  mytok = ParseNextToken (&parse, "\"");
  strcpy (ti.info, mytok);
  strcat (ti.info, "\n");

  while (toknr < 2 && (mytok = ParseNextToken (&parse, STDSEPERATOR)))
    {
      switch (toknr)
	{
	case 0:
	  if (Q_stricmp (mytok, "at") == 0)
	    toknr++;
	  else
	    {
	      _tourneyparseerror (parse, "\"at\" expected, %s found", mytok);
	      toknr = 1000;
	    }
	  break;

	case 1:
	  ti.attime = atoi (mytok);
	  toknr++;
	  break;
	}
    }
  if (toknr == 2)
    {

      memcpy (&t_eventlist[cevent], &ti, sizeof (tourneyindex_t));
      return true;
    }
  if (toknr < 2)
    {
      _tourneyparseerror (parse, "unexpected end of file in PRINT", NULL);
    }
  return false;
}
