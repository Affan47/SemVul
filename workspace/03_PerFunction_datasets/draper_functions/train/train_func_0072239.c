displaymigration_mark_window (GtkWidget *w)
{
  if (! displaymigration_initialised)
    {
      g_warning ("displaymigration not initialised yet");
      return;
    }

  if (GTK_WIDGET_REALIZED (w))
    {
      GdkWindow *window = w->window;

      gdk_window_add_filter (window, filter_func, NULL);

      reset_state (window);
      set_challenge_on_window (window);

      all_widgets = g_slist_append (all_widgets, w);

      g_signal_connect (G_OBJECT (w), "unrealize", G_CALLBACK (unrealize_window), NULL);
    }
  else
    g_signal_connect (G_OBJECT (w), "realize", G_CALLBACK (displaymigration_mark_window), NULL);
}
