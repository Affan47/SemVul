wnck_selector_get_screen (WnckSelector *selector)
{
  GdkScreen *screen;

  g_assert (gtk_widget_has_screen (GTK_WIDGET (selector)));

  screen = gtk_widget_get_screen (GTK_WIDGET (selector));

  return wnck_screen_get (gdk_screen_get_number (screen));
}
