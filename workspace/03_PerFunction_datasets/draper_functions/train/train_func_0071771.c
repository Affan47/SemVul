gst_value_deserialize_enum_iter_cmp (const GstFormatDefinition * format_def,
    const gchar * s)
{
  if (g_ascii_strcasecmp (s, format_def->nick) == 0)
    return 0;

  return g_ascii_strcasecmp (s, format_def->description);
}
