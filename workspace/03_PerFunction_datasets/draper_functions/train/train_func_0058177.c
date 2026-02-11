child_reap (EV_P_ int chain, int pid, int status)
{
  ev_child *w;
  int traced = WIFSTOPPED (status) || WIFCONTINUED (status);

  for (w = (ev_child *)childs [chain & ((EV_PID_HASHSIZE) - 1)]; w; w = (ev_child *)((WL)w)->next)
    {
      if ((w->pid == pid || !w->pid)
          && (!traced || (w->flags & 1)))
        {
          ev_set_priority (w, EV_MAXPRI);
          w->rpid    = pid;
          w->rstatus = status;
          ev_feed_event (EV_A_ (W)w, EV_CHILD);
        }
    }
}
