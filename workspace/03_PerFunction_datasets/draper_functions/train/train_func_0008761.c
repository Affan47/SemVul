main (int argc, char **argv)
{
  GtkWidget *window;
  GtkWidget *statistics;
  unsigned int i;

  gtk_init (&argc, &argv);
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "STATISTICS widget");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit),
                    NULL);
  statistics = gtk_statistics_new ();
  gtk_statistics_add_line (GTK_STATISTICS (statistics), "sin", "sin", "red");
  for (i = 0; i < 600; i++)
    gtk_statistics_update_value (GTK_STATISTICS (statistics), "sin", i,
                                 (uint64_t) (500 * (1.0 + sin (i / 100.0))));
  gtk_statistics_add_line (GTK_STATISTICS (statistics), "cos", "cos", "blue");
  for (i = 0; i < 600; i++)
    gtk_statistics_update_value (GTK_STATISTICS (statistics), "cos", i * 2,
                                 (uint64_t) (i * (1.0 + cos (i / 100.0))));
  g_signal_connect (G_OBJECT (window), "motion-notify-event",
                    G_CALLBACK (update), statistics);
  gtk_container_add (GTK_CONTAINER (window), statistics);
  gtk_widget_add_events (GTK_WIDGET (window), GDK_POINTER_MOTION_MASK);

  gtk_widget_show (statistics);
  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
