prefs_clicked (GtkWidget *button,
               gpointer   data)
{
  GtkWidget *prefs_dialog;
  GtkWidget *main_window = data;
  GConfClient *client;

  prefs_dialog = g_object_get_data (G_OBJECT (main_window), "prefs");

  if (prefs_dialog == NULL)
    {
      client = g_object_get_data (G_OBJECT (main_window), "client");

      prefs_dialog = create_prefs_dialog (main_window, client);

      g_object_set_data (G_OBJECT (main_window), "prefs", prefs_dialog);

      g_signal_connect (G_OBJECT (prefs_dialog), "destroy",
                        G_CALLBACK (prefs_dialog_destroyed),
                        main_window);

      gtk_widget_show_all (prefs_dialog);
    }
  else
    {

      gtk_window_present (GTK_WINDOW (prefs_dialog));
    }
}
