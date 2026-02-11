im_hangul_set_input_mode_info (GdkWindow *window, int state)
{
  if (window != NULL) {
    GdkScreen *screen = gdk_window_get_screen(window);
    im_hangul_set_input_mode_info_for_screen (screen, state);
  }
}
