gst_event_has_name (GstEvent * event, const gchar * name)
{
  g_return_val_if_fail (GST_IS_EVENT (event), FALSE);

  if (GST_EVENT_STRUCTURE (event) == NULL)
    return FALSE;

  return gst_structure_has_name (GST_EVENT_STRUCTURE (event), name);
}
