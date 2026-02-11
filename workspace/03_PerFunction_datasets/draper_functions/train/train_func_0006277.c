free_screen (rp_screen *s)
{
  rp_frame *frame;
  struct list_head *iter, *tmp;


  XSelectInput(dpy, RootWindow (dpy, s->screen_num), 0);

  list_for_each_safe_entry (frame, iter, tmp, &s->frames, node)
    {
      frame_free (s, frame);
    }

  deactivate_screen(s);

  XDestroyWindow (dpy, s->bar_window);
  XDestroyWindow (dpy, s->key_window);
  XDestroyWindow (dpy, s->input_window);
  XDestroyWindow (dpy, s->frame_window);
  XDestroyWindow (dpy, s->help_window);

#ifdef USE_XFT_FONT
  if (s->xft_font)
    {
      XftColorFree (dpy, DefaultVisual (dpy, s->screen_num),
                    DefaultColormap (dpy, s->screen_num), &s->xft_fg_color);
      XftColorFree (dpy, DefaultVisual (dpy, s->screen_num),
                    DefaultColormap (dpy, s->screen_num), &s->xft_bg_color);
      XftFontClose (dpy, s->xft_font);
    }
#endif

  XFreeCursor (dpy, s->rat);
  XFreeColormap (dpy, s->def_cmap);
  XFreeGC (dpy, s->normal_gc);
  XFreeGC (dpy, s->inverse_gc);

  free (s->display_string);
}
