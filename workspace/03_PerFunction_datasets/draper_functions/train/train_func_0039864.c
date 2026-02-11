makeargv (void)
{
  register char *cp, *cp2, c;
  register char **argp = margv;

  margc = 0;
  cp = line;
  if (*cp == '!')
    {
      strcpy (saveline, line);
      *argp++ = "!";
      margc++;
      cp++;
    }
  while ((c = *cp))
    {
      register int inquote = 0;
      while (isspace (c))
	c = *++cp;
      if (c == '\0')
	break;
      *argp++ = cp;
      margc += 1;
      for (cp2 = cp; c != '\0'; c = *++cp)
	{
	  if (inquote)
	    {
	      if (c == inquote)
		{
		  inquote = 0;
		  continue;
		}
	    }
	  else
	    {
	      if (c == '\\')
		{
		  if ((c = *++cp) == '\0')
		    break;
		}
	      else if (c == '"')
		{
		  inquote = '"';
		  continue;
		}
	      else if (c == '\'')
		{
		  inquote = '\'';
		  continue;
		}
	      else if (isspace (c))
		break;
	    }
	  *cp2++ = c;
	}
      *cp2 = '\0';
      if (c == '\0')
	break;
      cp++;
    }
  *argp++ = 0;
}
