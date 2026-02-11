group_prev_window (rp_group *g, rp_window *win)
{
  rp_window_elem *cur, *we;


  if (win == NULL)
    return group_last_window (g, current_screen());


  we = group_find_window (&g->mapped_windows, win);
  if (we == NULL)
    return group_last_window (g, win->scr);


  for (cur = list_prev_entry (we, &g->mapped_windows, node);
       cur != we;
       cur = list_prev_entry (cur, &g->mapped_windows, node))
    {
      if (!find_windows_frame (cur->win) && (cur->win->scr == win->scr || rp_have_xinerama))
        {
          return cur->win;
        }
    }

  return NULL;

}
