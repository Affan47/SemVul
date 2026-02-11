gdict_window_cmd_file_new (GSimpleAction   *action,
                           GVariant        *parameter,
                           gpointer         user_data)
{
  GdictWindow *window = user_data;
  GtkWidget *new_window;
  gchar *word = NULL;

  gdict_window_store_state (window);

  word = gdict_defbox_get_selected_word (GDICT_DEFBOX (window->defbox));
  if (word)
    {
      new_window = gdict_window_new (GDICT_WINDOW_ACTION_LOOKUP,
                                     window->loader,
                                     NULL,
                                     NULL,
                                     NULL,
                                     word);
      g_free (word);
    }
  else
    new_window = gdict_window_new (GDICT_WINDOW_ACTION_CLEAR,
                                   window->loader,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL);

  gtk_window_set_application (GTK_WINDOW (new_window),
                              gtk_window_get_application (GTK_WINDOW (window)));
  gtk_widget_show (new_window);

  g_signal_emit (window, gdict_window_signals[CREATED], 0, new_window);
}
