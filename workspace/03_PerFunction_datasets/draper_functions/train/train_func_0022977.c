create_win1()
{
  if (gwin1)
    return;

  gwin1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_has_resize_grip(GTK_WINDOW(gwin1), FALSE);
  gtk_widget_realize (gwin1);

  set_no_focus(gwin1);

  g_signal_connect (G_OBJECT (gwin1), "scroll-event", G_CALLBACK (button_scroll_event_tsin), NULL);
}
