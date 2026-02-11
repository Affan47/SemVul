error_cb (GdictContext *context,
          const GError *error,
	  gpointer      user_data)
{
  GdictDatabaseChooser *chooser = GDICT_DATABASE_CHOOSER (user_data);

  if (gtk_widget_get_window (GTK_WIDGET (chooser)))
    gdk_window_set_cursor (gtk_widget_get_window (GTK_WIDGET (chooser)), NULL);

  chooser->priv->is_searching = FALSE;
  chooser->priv->results = 0;
}
