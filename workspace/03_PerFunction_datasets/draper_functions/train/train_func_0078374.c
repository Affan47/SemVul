save_sig_handlers (void)
{
  int i;

  DPRINTF("saving signal handlers\n");
  for (i = SIGRTMAX; i > 0; --i) {
    if (mtcp_sigaction (i, NULL, &sigactions[i]) < 0) {
      if (errno == EINVAL)
         memset (&sigactions[i], 0, sizeof sigactions[i]);
      else {
        MTCP_PRINTF("error saving signal %d action: %s\n", i, strerror(errno));
        mtcp_abort ();
      }
    }

    if (sigactions[i].sa_handler != SIG_DFL) {
      DPRINTF("saving signal handler (non-default) for %d -> %p\n",
              i, (sigactions[i].sa_flags & SA_SIGINFO ?
                  (void *)(sigactions[i].sa_sigaction) :
                  (void *)(sigactions[i].sa_handler)));
    }
  }
}
