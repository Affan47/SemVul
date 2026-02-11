get_child_info (Window w)
{
  rp_child_info *cur;
  int status;
  int pid;
  Atom type_ret;
  int format_ret;
  unsigned long nitems;
  unsigned long bytes_after;
  unsigned char *req;
  pid_t sid;

  status = XGetWindowProperty (dpy, w, _net_wm_pid,
                               0, 0, False, XA_CARDINAL,
                               &type_ret, &format_ret, &nitems, &bytes_after, &req);

  if (status != Success || req == NULL)
    {
      PRINT_DEBUG (("Couldn't get _NET_WM_PID Property\n"));
      return NULL;
    }


  XFree (req);

  status = XGetWindowProperty (dpy, w, _net_wm_pid,
                               0, (bytes_after / 4) + (bytes_after % 4 ? 1 : 0),
                               False, XA_CARDINAL, &type_ret, &format_ret, &nitems,
                               &bytes_after, &req);

  if (status != Success || req == NULL)
    {
      PRINT_DEBUG (("Couldn't get _NET_WM_PID Property\n"));
      return NULL;
    }

  pid = *((int *)req);
  XFree(req);

  PRINT_DEBUG(("pid: %d\n", pid));


  sid = getsid (pid);
  list_for_each_entry (cur, &rp_children, node)
    {
      PRINT_DEBUG(("cur->pid=%d sid=%d\n", cur->pid, getsid (cur->pid)));
      if (sid == getsid (cur->pid))
        return cur;
    }

  return NULL;
}
