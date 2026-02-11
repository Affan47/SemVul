suspend_screenhack (saver_screen_info *ssi, Bool suspend_p)
{
#ifdef SIGSTOP
  saver_info *si = ssi->global;
  if (ssi->pid)
    kill_job (si, ssi->pid, (suspend_p ? SIGSTOP : SIGCONT));
#endif
}
