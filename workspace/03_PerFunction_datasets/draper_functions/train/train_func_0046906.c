posix_request_interrupts(s48_call_t call, s48_ref_t sch_signum)
{
  int			signum = s48_extract_long_2(call, sch_signum);
  struct sigaction	sa;

  if (saved_actions[signum] == NULL) {
    struct sigaction *	old = (struct sigaction *)
                                malloc(sizeof(struct sigaction));

    if (old == NULL)
      s48_out_of_memory_error();

    sa.sa_handler = generic_interrupt_catcher;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(signum, &sa, old) != 0) {
      free(old);
      s48_os_error_2(call, "posix_request_interrupts", errno, 1, sch_signum); }

    saved_actions[signum] = old; }

  return s48_unspecific_2(call);
}
