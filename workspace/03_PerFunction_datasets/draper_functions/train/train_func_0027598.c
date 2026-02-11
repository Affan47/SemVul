scanwins(rp_screen *s)
{
  rp_window *win;
  XWindowAttributes attr;
  unsigned int i, nwins;
  Window dw1, dw2, *wins;

  XQueryTree(dpy, s->root, &dw1, &dw2, &wins, &nwins);
  PRINT_DEBUG (("windows: %d\n", nwins));

  for (i = 0; i < nwins; i++)
    {
      XGetWindowAttributes(dpy, wins[i], &attr);
      if (is_rp_window_for_screen(wins[i], s)
          || attr.override_redirect == True
          || unmanaged_window (wins[i])) continue;


      {
        XWindowAttributes root_attr;

        XGetWindowAttributes (dpy, s->root, &root_attr);
      PRINT_DEBUG (("attrs: %d %d %d %d %d %d\n", root_attr.x, root_attr.y,
                    s->left, s->top, s->left + s->width, s->top + s->height));}

      if (rp_have_xinerama
          && ((attr.x > s->left + s->width)
               || (attr.x < s->left)
               || (attr.y > s->top + s->height)
               || (attr.y < s->top))) continue;

      win = add_to_window_list (s, wins[i]);

      PRINT_DEBUG (("map_state: %s\n",
                    attr.map_state == IsViewable ? "IsViewable":
                    attr.map_state == IsUnviewable ? "IsUnviewable" : "IsUnmapped"));
      PRINT_DEBUG (("state: %s\n",
                    get_state(win) == IconicState ? "Iconic":
                    get_state(win) == NormalState ? "Normal" : "Other"));


      if (attr.map_state == IsViewable
          || (attr.map_state == IsUnmapped
              && get_state (win) == IconicState))
        map_window (win);
    }

  XFree(wins);
}
