search_find_callback (GtkAction *action,
		      TerminalWindow *window)
{
  TerminalWindowPrivate *priv = window->priv;

  if (!priv->search_find_dialog) {
    GtkWidget *dialog;

    dialog = priv->search_find_dialog = terminal_search_dialog_new (GTK_WINDOW (window));

    g_signal_connect (dialog, "destroy",
		      G_CALLBACK (gtk_widget_destroyed), &priv->search_find_dialog);
    g_signal_connect (dialog, "response",
		      G_CALLBACK (search_find_response_callback), window);
    g_signal_connect (dialog, "delete-event",
		     G_CALLBACK (search_dialog_delete_event_cb), NULL);
  }

  terminal_search_dialog_present (priv->search_find_dialog);
}
