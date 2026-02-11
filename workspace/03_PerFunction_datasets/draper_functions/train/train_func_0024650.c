restore_calling_window (void)
{
  register WINDOW *win, *compwin = NULL;


  for (win = windows; win; win = win->next)
    {
      if (completions_window_p (win))
        compwin = win;

      if (win == calling_window && win == compwin)
        {
          window_set_node_of_window (calling_window, calling_window_node);
          calling_window->point = calling_window_point;
          calling_window->pagetop = calling_window_pagetop;
          compwin = NULL;
          break;
        }
    }


  if (compwin)
    {
      if ((compwin != windows || windows->next) &&
          !echo_area_stack_contains_completions_p ())
        {
          WINDOW *next;
          int pagetop = 0;
          int start = 0;
          int end = 0;
          int amount = 0;

          next = compwin->next;
          if (next)
            {
              start = next->first_row;
              end = start + next->height;
              amount = - (compwin->height + 1);
              pagetop = next->pagetop;
            }

          info_delete_window_internal (compwin);


#if defined (UNNECESSARY)
          echo_area_completions_window = NULL;
#endif

          if (next)
            {
              display_scroll_display (start, end, amount);
              next->pagetop = pagetop;
              display_update_display (windows);
            }
        }
    }
}
