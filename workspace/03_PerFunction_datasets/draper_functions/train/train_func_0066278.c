ignore_sigpipe()
{
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    fatal_abort("SIGPIPE SIG_IGN");
  }
}
