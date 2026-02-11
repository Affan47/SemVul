construct_simple_presence_value_array (TpPresenceStatus *status,
    const TpPresenceStatusSpec *supported_statuses)
{
  TpConnectionPresenceType status_type;
  const gchar *status_name;
  const gchar *message = NULL;
  GValueArray *presence;

  status_name = supported_statuses[status->index].name;
  status_type = supported_statuses[status->index].presence_type;

  if (status->optional_arguments != NULL)
    {
      GValue *val;
      val = g_hash_table_lookup (status->optional_arguments, "message");
      if (val != NULL)
        message = g_value_get_string (val);
    }

  if (message == NULL)
    message = "";

  presence = g_value_array_new (3);

  g_value_array_append (presence, NULL);
  g_value_init (g_value_array_get_nth (presence, 0), G_TYPE_UINT);
  g_value_set_uint (g_value_array_get_nth (presence, 0), status_type);

  g_value_array_append (presence, NULL);
  g_value_init (g_value_array_get_nth (presence, 1), G_TYPE_STRING);
  g_value_set_string (g_value_array_get_nth (presence, 1), status_name);

  g_value_array_append (presence, NULL);
  g_value_init (g_value_array_get_nth (presence, 2), G_TYPE_STRING);
  g_value_set_string (g_value_array_get_nth (presence, 2), message);

  return presence;
}
