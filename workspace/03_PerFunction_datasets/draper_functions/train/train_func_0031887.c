destroy_window (XDestroyWindowEvent *ev)
{
  rp_window *win;

  win = find_window (ev->window);
  if (win == NULL) return;

  ignore_badwindow++;


  if (win->state == IconicState)
    {
      PRINT_DEBUG (("Destroying Iconic Window (%s)\n", window_name (win)));
      withdraw_window (win);
    }
  else if (win->state == NormalState)
    {
      rp_frame *frame;

      PRINT_DEBUG (("Destroying Normal Window (%s)\n", window_name (win)));
      frame = find_windows_frame (win);
      if (frame)
        {
          cleanup_frame (frame);
          if (frame->number == win->scr->current_frame
              && current_screen() == win->scr)
            set_active_frame (frame, 0);
        }

      if (frame->win_number != EMPTY)
	hook_run (&rp_switch_win_hook);
      withdraw_window (win);
    }


  unmanage (win);
  ignore_badwindow--;
}
