__libc_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
  struct sigaction *newact = (struct sigaction *)act;
  if (act) {
	newact = alloca(sizeof(*newact));
	newact->sa_handler = act->sa_handler;
	newact->sa_flags = act->sa_flags | SA_RESTORER;
	newact->sa_restorer = &__restore_rt;
	newact->sa_mask = act->sa_mask;
  }
  return __rt_sigaction(signum, newact, oldact, _NSIG/8);
}
