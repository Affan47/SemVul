gst_format_get_name (GstFormat format)
{
  const GstFormatDefinition *def;
  const gchar *result;

  if ((def = gst_format_get_details (format)) != NULL)
    result = def->nick;
  else
    result = NULL;

  return result;
}
