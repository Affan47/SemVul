meta_ui_window_is_widget (MetaUI *ui,
                          Window  xwindow)
{
  GdkDisplay *display;
  GdkWindow *window;

  display = gdk_x11_lookup_xdisplay (ui->xdisplay);
  window = gdk_x11_window_lookup_for_display (display, xwindow);

  if (window)
    {
      void *user_data = NULL;
      gdk_window_get_user_data (window, &user_data);
      return user_data != NULL && user_data != ui->frames;
    }
  else
    return FALSE;
}
