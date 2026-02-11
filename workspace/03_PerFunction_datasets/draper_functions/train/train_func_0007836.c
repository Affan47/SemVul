usset_signal (isig, pfn, fforce, pfignored)
     int isig;
     RETSIGTYPE (*pfn) P((int));
     boolean fforce;
     boolean *pfignored;
{
#if HAVE_SIGACTION

  struct sigaction s;

  if (! fforce)
    {
      (void) (sigemptyset (&s.sa_mask));
      if (sigaction (isig, (struct sigaction *) NULL, &s) != 0)
	ulog (LOG_FATAL, "sigaction (%d): %s", isig, strerror (errno));

      if (s.sa_handler == SIG_IGN)
	{
	  if (pfignored != NULL)
	    *pfignored = TRUE;
	  return;
	}

      if (pfignored != NULL)
	*pfignored = FALSE;
    }

  s.sa_handler = pfn;
  (void) (sigemptyset (&s.sa_mask));
  s.sa_flags = SA_INTERRUPT;

  if (sigaction (isig, &s, (struct sigaction *) NULL) != 0)
    ulog (LOG_FATAL, "sigaction (%d): %s", isig, strerror (errno));

#else
#if HAVE_SIGVEC

  struct sigvec s;

  if (! fforce)
    {
      if (sigvec (isig, (struct sigvec *) NULL, &s) != 0)
	ulog (LOG_FATAL, "sigvec (%d): %s", isig, strerror (errno));

      if (s.sv_handler == SIG_IGN)
	{
	  if (pfignored != NULL)
	    *pfignored = TRUE;
	  return;
	}

      if (pfignored != NULL)
	*pfignored = FALSE;
    }

  s.sv_handler = pfn;
  s.sv_mask = 0;
  s.sv_flags = SV_INTERRUPT;

  if (sigvec (isig, &s, (struct sigvec *) NULL) != 0)
    ulog (LOG_FATAL, "sigvec (%d): %s", isig, strerror (errno));

#else

  if (! fforce)
    {
      if (signal (isig, SIG_IGN) == SIG_IGN)
	{
	  if (pfignored != NULL)
	    *pfignored = TRUE;
	  return;
	}

      if (pfignored != NULL)
	*pfignored = FALSE;
    }

  (void) signal (isig, pfn);

#endif
#endif
}
