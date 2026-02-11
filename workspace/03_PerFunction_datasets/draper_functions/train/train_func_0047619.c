cread (o, pqbuf)
     int o;
     struct sbuf **pqbuf;
{
  long ctotal;

  while (*pqbuf != NULL && (*pqbuf)->qnext != NULL)
    pqbuf = &(*pqbuf)->qnext;

  ctotal = 0;

  while (TRUE)
    {
      int cgot;

      if (*pqbuf != NULL
	  && (size_t) (*pqbuf)->cend >= sizeof (*pqbuf)->ab)
	pqbuf = &(*pqbuf)->qnext;

      if (*pqbuf == NULL)
	{
	  *pqbuf = (struct sbuf *) malloc (sizeof (struct sbuf));
	  if (*pqbuf == NULL)
	    {
	      fprintf (stderr, "Out of memory\n");
	      uchild (SIGCHLD);
	    }
	  (*pqbuf)->qnext = NULL;
	  (*pqbuf)->cstart = 0;
	  (*pqbuf)->cend = 0;
	}

      cgot = read (o, (*pqbuf)->ab + (*pqbuf)->cend,
		   (sizeof (*pqbuf)->ab) - (*pqbuf)->cend);
      if (cgot < 0)
	{
	  if (errno == EAGAIN || errno == EWOULDBLOCK || errno == ENODATA)
	    cgot = 0;
	  else
	    {
	      perror ("read");
	      uchild (SIGCHLD);
	    }
	}

      if (cgot == 0)
	return ctotal;

      ctotal += cgot;

      if (zDebug != NULL)
	{
	  char abshow[325];
	  char *zfrom;
	  char *zshow;
	  int i;

	  zfrom = (*pqbuf)->ab + (*pqbuf)->cend;
	  zshow = abshow;
	  for (i = 0; i < cgot && i < 80; i++, zfrom++)
	    zshow += cpshow (zshow, *zfrom);
	  if (i < cgot)
	    {
	      *zshow++ = '.';
	      *zshow++ = '.';
	      *zshow++ = '.';
	    }
	  *zshow = '\0';
	  fprintf (stderr, "Read from %d: %d \"%s\"\n", o, cgot, abshow);
	  fflush (stderr);
	}

      if (iPercent > 0)
	{
	  int i;
	  int c;

	  c = 0;
	  for (i = 0; i < cgot; i++)
	    {
	      if (rand () % 1000 < iPercent)
		{
		  ++(*pqbuf)->ab[(*pqbuf)->cend + i];
		  ++c;
		}
	    }
	  if (zDebug != NULL && c > 0)
	    fprintf (stderr, "Clobbered %d bytes\n", c);
	}

      (*pqbuf)->cend += cgot;

      if (ctotal > 256)
	return ctotal;
    }
}
