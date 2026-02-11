tp_debug_sender_add_message (TpDebugSender *self,
    GTimeVal *timestamp,
    const gchar *domain,
    GLogLevelFlags level,
    const gchar *string)
{
  GTimeVal now = { 0 };

  if (timestamp == NULL)
    {
      g_get_current_time (&now);
      timestamp = &now;
    }

  _tp_debug_sender_take (self,
      debug_message_new (timestamp, domain, level, string));
}
