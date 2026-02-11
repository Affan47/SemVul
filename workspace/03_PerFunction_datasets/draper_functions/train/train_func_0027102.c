_tp_debug_message_new (gdouble timestamp,
    const gchar *domain,
    TpDebugLevel level,
    const gchar *message)
{
  TpDebugMessage *self;
  GTimeVal tv;

  g_return_val_if_fail (domain != NULL, NULL);
  g_return_val_if_fail (message != NULL, NULL);

  self = g_object_new (TP_TYPE_DEBUG_MESSAGE,
      NULL);

  tv.tv_sec = (glong) timestamp;
  tv.tv_usec = ((timestamp - (int) timestamp) * 1e6);

  if (g_strrstr (domain, "/"))
    {
      gchar **parts = g_strsplit (domain, "/", 2);
      self->priv->domain = g_strdup (parts[0]);
      self->priv->category = g_strdup (parts[1]);
      g_strfreev (parts);
    }
  else
    {
      self->priv->domain = g_strdup (domain);
      self->priv->category = NULL;
    }

  self->priv->time = g_date_time_new_from_timeval_utc (&tv);

  self->priv->level = debug_level_to_log_level_flags (level);
  self->priv->message = g_strdup (message);
  g_strchomp (self->priv->message);

  return self;
}
