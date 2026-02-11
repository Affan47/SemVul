_gst_format_initialize (void)
{
  GstFormatDefinition *standards = standard_definitions;

  g_static_mutex_lock (&mutex);
  if (_nick_to_format == NULL) {
    _nick_to_format = g_hash_table_new (g_str_hash, g_str_equal);
    _format_to_nick = g_hash_table_new (NULL, NULL);
  }

  while (standards->nick) {
    standards->quark = g_quark_from_static_string (standards->nick);
    g_hash_table_insert (_nick_to_format, (gpointer) standards->nick,
        standards);
    g_hash_table_insert (_format_to_nick, GINT_TO_POINTER (standards->value),
        standards);

    _gst_formats = g_list_append (_gst_formats, standards);
    standards++;
    _n_values++;
  }

  g_type_class_ref (gst_format_get_type ());
  g_static_mutex_unlock (&mutex);
}
