store_call (TplCallChannel *self)
{
  TplCallChannelPriv *priv = self->priv;
  GError *error = NULL;
  TplCallEvent *call_log;
  TplLogManager *logmanager;
  const gchar *channel_path = tp_proxy_get_object_path (TP_PROXY (self));
  GTimeSpan duration = -1;

  if (priv->timer_started)
    duration = g_timer_elapsed (priv->timer, NULL);


  call_log = g_object_new (TPL_TYPE_CALL_EVENT,

      "account", priv->account,
      "channel-path", channel_path,
      "receiver", priv->receiver,
      "sender", priv->sender,
      "timestamp", g_date_time_to_unix (priv->timestamp),

      "duration", duration,
      "end-actor", priv->end_actor,
      "end-reason", priv->end_reason,
      "detailed-end-reason", priv->detailed_end_reason,
      NULL);

  logmanager = tpl_log_manager_dup_singleton ();
  _tpl_log_manager_add_event (logmanager, TPL_EVENT (call_log), &error);

  if (error != NULL)
    {
      PATH_DEBUG (self, "TplCallChannel: %s", error->message);
      g_error_free (error);
    }

  g_object_unref (logmanager);
  g_object_unref (call_log);
}
