window_show_cb (GtkWidget *w,
                G_GNUC_UNUSED gpointer data)
{
  int x = 0;
  int y = 0;

  GmWindow *self = NULL;

  gchar *conf_key_size = NULL;
  gchar *conf_key_position = NULL;
  gchar *size = NULL;
  gchar *position = NULL;
  gchar **couple = NULL;

  self = GM_WINDOW (w);

  g_return_if_fail (g_strcmp0 (self->priv->key, ""));

  conf_key_position =
    g_strdup_printf ("%s/position", self->priv->key);
  conf_key_size =
    g_strdup_printf ("%s/size", self->priv->key);

  if (gtk_window_get_resizable (GTK_WINDOW (w))) {

    size = gm_conf_get_string (conf_key_size);
    if (size)
      couple = g_strsplit (size, ",", 0);

    if (couple && couple [0])
      x = atoi (couple [0]);
    if (couple && couple [1])
      y = atoi (couple [1]);

    if (x > 0 && y > 0) {
      gtk_window_resize (GTK_WINDOW (w), x, y);
    }

    g_strfreev (couple);
    g_free (size);
  }

  position = gm_conf_get_string (conf_key_position);
  if (position)
    couple = g_strsplit (position, ",", 0);

  if (couple && couple [0])
    x = atoi (couple [0]);
  if (couple && couple [1])
    y = atoi (couple [1]);

  if (x != 0 && y != 0)
    gtk_window_move (GTK_WINDOW (w), x, y);

  g_strfreev (couple);
  couple = NULL;
  g_free (position);

  gtk_widget_realize (GTK_WIDGET (w));

  g_free (conf_key_position);
  g_free (conf_key_size);
}
