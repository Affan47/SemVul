s48_sysdep_init(void)
{
#ifdef HAVE_PTHREAD_H
  main_thread = pthread_self();
#endif

#ifdef HAVE_SIGALTSTACK
  stack_t ss;

  ss.ss_sp = malloc(SIGSTKSZ);
  if (ss.ss_sp == NULL)
    fprintf(stderr,
	    "Failed to malloc alt stack, errno = %d\n",
	    errno);
  ss.ss_size = SIGSTKSZ;
  ss.ss_flags = 0;
  if (sigaltstack(&ss, NULL) == -1)
    fprintf(stderr,
	    "Failed to sigaltstack, errno = %d\n",
	    errno);
#endif

#if defined HAVE_GLIB
  g_main_context = g_main_context_default();
  g_main_context_ref(g_main_context);
  g_source = (S48_GSource *) g_source_new(&s48_g_source_funcs, sizeof (S48_GSource));
  g_source_id = g_source_attach((GSource *) g_source, g_main_context);

  g_pollfds_size = FD_SETSIZE;
  g_pollfds = (GPollFD *) calloc (sizeof (GPollFD), g_pollfds_size);

  if (g_pollfds == NULL) {
    fprintf(stderr,
	    "Failed to alloc array of file descriptors to poll with %d elements, errno = %d\n",
	    g_pollfds_size,
	    errno);
    exit(1);
  }
#elif defined HAVE_POLL
  pollfds_size = FD_SETSIZE;
  pollfds = (struct pollfd *) calloc (sizeof (struct pollfd), pollfds_size);

  if (pollfds == NULL) {
    fprintf(stderr,
	    "Failed to alloc array of file descriptors to poll with %ld elements, errno = %d\n",
	    pollfds_size,
	    errno);
    exit(1);
  }
#endif

  fd_setsize = FD_SETSIZE;
  fds = (fd_struct **) calloc (sizeof (fd_struct *), fd_setsize);

  if (fds == NULL) {
    fprintf(stderr,
	    "Failed to alloc fds with %ld elements, errno = %d\n",
	    fd_setsize,
	    errno);
    exit(1);
  }

  if (!s48_setcatcher(SIGINT, s48_when_keyboard_interrupt)
      || !s48_setcatcher(SIGALRM, s48_when_alarm_interrupt)
      || !s48_setcatcher(SIGPIPE, when_sigpipe_interrupt)
      || !s48_setcatcher(SIG_EXTERNAL_EVENT, s48_when_external_event_interrupt)) {
    fprintf(stderr,
	    "Failed to install signal handlers, errno = %d\n",
	    errno);
    exit(1);
  }

  sigemptyset(&interrupt_mask);
  sigaddset(&interrupt_mask, SIGINT);
  sigaddset(&interrupt_mask, SIGALRM);

  s48_start_alarm_interrupts();
}
