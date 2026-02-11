gamgi_gtk_statusbar_mode (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;

if (window->demo_flag == 0)
  {
  window->timer_progress = g_timeout_add (GAMGI_GTK_STATUSBAR_PROGRESS_TIME,
  gamgi_gtk_statusbar_progress, window);
  gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (window->progress_bar), 0.0);
  gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (window->progress_bar),
  GTK_PROGRESS_LEFT_TO_RIGHT);
  gtk_widget_show (window->progress_bar);
  window->demo_flag = 1;
  }
else if (window->demo_flag == 1)
  {
  gtk_progress_bar_set_pulse_step (GTK_PROGRESS_BAR (window->progress_bar),
  GAMGI_GTK_STATUSBAR_PROGRESS_FRACTION);
  window->demo_flag = 2;
  }
else if (window->demo_flag == 2)
  {
  gtk_widget_hide (window->progress_bar);
  g_source_remove (window->timer_progress);
  window->timer_progress = 0;
  window->demo_flag = 0;
  }
}
