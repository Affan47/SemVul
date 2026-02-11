reader_process (void *pv)
{
  struct hp3500_data *scanner = pv;
  time_t t;
  sigset_t ignore_set;
  sigset_t sigterm_set;
  struct SIGACTION act;
  struct hp3500_write_info winfo;
  int status;

  if (sanei_thread_is_forked ())
    {
      close (scanner->pipe_r);

      sigfillset (&ignore_set);
      sigdelset (&ignore_set, SIGTERM);
#if     defined (__APPLE__) && defined (__MACH__)
      sigdelset (&ignore_set, SIGUSR2);
#endif
      sigprocmask (SIG_SETMASK, &ignore_set, 0);

      sigemptyset (&sigterm_set);
      sigaddset (&sigterm_set, SIGTERM);

      memset (&act, 0, sizeof (act));
#ifdef     _POSIX_SOURCE
      act.sa_handler = sigtermHandler;
#endif
      sigaction (SIGTERM, &act, 0);
    }


  time (&t);
  do_warmup = (t - scanner->last_scan) > 300;

  if (getenv ("HP3500_NOWARMUP") && atoi (getenv ("HP3500_NOWARMUP")) > 0)
    do_warmup = 0;

  udh = scanner->sfd;

  cancelled_scan = 0;

  winfo.scanner = scanner;
  winfo.bytesleft =
    scanner->bytes_per_scan_line * scanner->scan_height_pixels;

  if (getenv ("HP3500_SLEEP"))
    {
      int seconds = atoi (getenv ("HP3500_SLEEP"));

      DBG (1, "Backend process %d sleeping for %d seconds\n", getpid (),
	   seconds);
      sleep (seconds);
    }
  DBG (10, "Scanning at %ddpi, mode=%s\n", scanner->resolution,
       scan_mode_list[scanner->mode]);
  if (rts8801_scan
      (scanner->actres_pixels.left + 250 * scanner->resolution / 1200,
       scanner->actres_pixels.top + 599 * scanner->resolution / 1200,
       scanner->actres_pixels.right - scanner->actres_pixels.left,
       scanner->actres_pixels.bottom - scanner->actres_pixels.top,
       scanner->resolution, scanner->mode, scanner->brightness,
       scanner->contrast, (rts8801_callback) writefunc, &winfo) >= 0)
    status = SANE_STATUS_GOOD;
  status = SANE_STATUS_IO_ERROR;
  close (scanner->pipe_w);
  return status;
}
