cmd_cnext (int interactive, struct cmdarg **args)
{
  rp_window *cur, *last, *win;

  cur = current_window();
  if (!cur || !cur->res_class)
    return cmd_next (interactive, args);


  last = group_prev_window (rp_current_group, cur);

  if (last)
    for (win = group_next_window (rp_current_group, cur);
         win;
         win = group_next_window (rp_current_group, win))
      {
        if (win->res_class
            && strcmp (cur->res_class, win->res_class))
          {
            set_active_window_force (win);
            return cmdret_new (RET_SUCCESS, NULL);
          }

        if (win == last) break;
      }

  return cmdret_new (RET_FAILURE, "%s", MESSAGE_NO_OTHER_WINDOW);
}
