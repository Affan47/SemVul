gdict_window_cmd_file_close_window (GSimpleAction *action,
                                    GVariant      *parameter,
                                    gpointer       user_data)
{
  GdictWindow *window = user_data;

  g_assert (GDICT_IS_WINDOW (window));

  gdict_window_store_state (window);


  if (action)
    gtk_widget_destroy (GTK_WIDGET (window));
}
