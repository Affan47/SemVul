SignalHandler(int signum, siginfo_t *si, void *data) {
  if (sig_pids != NULL) {
    if (signum == SIGABRT) {
      while (sig_num_threads-- > 0) {


        sys_sched_yield();
        sys_ptrace(PTRACE_KILL, sig_pids[sig_num_threads], 0, 0);
      }
    } else if (sig_num_threads > 0) {
      ResumeAllProcessThreads(sig_num_threads, (int *)sig_pids);
    }
  }
  sig_pids = NULL;
  if (sig_marker >= 0)
    NO_INTR(sys_close(sig_marker));
  sig_marker = -1;
  if (sig_proc >= 0)
    NO_INTR(sys_close(sig_proc));
  sig_proc = -1;

  sys__exit(signum == SIGABRT ? 1 : 2);
}
