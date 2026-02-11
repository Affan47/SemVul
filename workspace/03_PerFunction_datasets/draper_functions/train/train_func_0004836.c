fsysdep_cu_copy (fcopy)
     boolean fcopy;
{
  int ierr;
  int c;

  usset_signal (SIGALRM, uscu_alarm_kill, TRUE, (boolean *) NULL);
  if (fcopy)
    iSsend_sig = SIGUSR1;
  else
    iSsend_sig = SIGUSR2;

  uscu_alarm_kill (SIGALRM);

  alarm (1);

  while (TRUE)
    {
      char b;

      c = read (oSpipe, &b, 1);

#if DEBUG > 1
      if (c > 0)
	DEBUG_MESSAGE1 (DEBUG_INCOMING,
			"fsysdep_cu_copy: Got '%d'", b);
#endif

      if ((c < 0 && errno != EINTR)
	  || c == 0
	  || (c > 0 && b == (fcopy ? CHILD_STARTED : CHILD_STOPPED)))
	break;


    }

  ierr = errno;

  usset_signal (SIGALRM, SIG_IGN, TRUE, (boolean *) NULL);
  alarm (0);

  if (c > 0)
    return TRUE;

  if (c == 0)
    ulog (LOG_ERROR, "EOF on child pipe");
  else
    ulog (LOG_ERROR, "read: %s", strerror (ierr));

  return FALSE;
}
