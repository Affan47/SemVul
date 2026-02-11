gst_format_get_by_nick (const gchar * nick)
{
  GstFormatDefinition *format;

  g_return_val_if_fail (nick != NULL, GST_FORMAT_UNDEFINED);

  g_mutex_lock (&mutex);
  format = g_hash_table_lookup (_nick_to_format, nick);
  g_mutex_unlock (&mutex);

  if (format != NULL)
    return format->value;
  else
    return GST_FORMAT_UNDEFINED;
}
