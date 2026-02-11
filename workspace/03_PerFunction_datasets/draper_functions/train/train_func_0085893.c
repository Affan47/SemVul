map_request (XEvent *ev)
{
  rp_window *win;

  win = find_window (ev->xmap.window);
  if (win == NULL)
    {
      PRINT_DEBUG (("Map request from an unknown window.\n"));
      XMapWindow (dpy, ev->xmap.window);
      return;
    }

  PRINT_DEBUG (("Map request from a managed window\n"));

  switch (win->state)
    {
    case WithdrawnState:
      if (unmanaged_window (win->w))
        {
          PRINT_DEBUG (("Mapping Unmanaged Window\n"));
          XMapWindow (dpy, win->w);
          break;
        }
      else
        {
          PRINT_DEBUG (("Mapping Withdrawn Window\n"));
          map_window (win);
          break;
        }
      break;
    case IconicState:
      PRINT_DEBUG (("Mapping Iconic window\n"));
      if (win->last_access == 0)
        {


          if ((rp_honour_transient_map && win->transient)
              || (rp_honour_normal_map && !win->transient))
            set_active_window (win);
        }
      else
        {


          if ((rp_honour_transient_raise && win->transient)
              || (rp_honour_normal_raise && !win->transient))
            set_active_window (win);
          else
            show_rudeness_msg (win, 1);
        }
      break;
    }
}
