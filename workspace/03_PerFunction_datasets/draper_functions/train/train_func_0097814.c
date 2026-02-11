handle_redirect_message (GstURIDecodeBin * dec, GstMessage * msg)
{
  const GValue *locations_list, *location_val;
  GstMessage *new_msg;
  GstStructure *new_structure = NULL;
  GList *l_good = NULL, *l_neutral = NULL, *l_bad = NULL;
  GValue new_list = { 0, };
  guint size, i;
  const GstStructure *structure;

  GST_DEBUG_OBJECT (dec, "redirect message: %" GST_PTR_FORMAT, msg);
  GST_DEBUG_OBJECT (dec, "connection speed: %" G_GUINT64_FORMAT,
      dec->connection_speed);

  structure = gst_message_get_structure (msg);
  if (dec->connection_speed == 0 || structure == NULL)
    return msg;

  locations_list = gst_structure_get_value (structure, "locations");
  if (locations_list == NULL)
    return msg;

  size = gst_value_list_get_size (locations_list);
  if (size < 2)
    return msg;


  for (i = 0; i < size; ++i) {
    const GstStructure *s;
    gint bitrate = 0;

    location_val = gst_value_list_get_value (locations_list, i);
    s = (const GstStructure *) g_value_get_boxed (location_val);
    if (!gst_structure_get_int (s, "minimum-bitrate", &bitrate) || bitrate <= 0) {
      GST_DEBUG_OBJECT (dec, "no bitrate: %" GST_PTR_FORMAT, s);
      l_neutral = g_list_append (l_neutral, (gpointer) s);
    } else if (bitrate > dec->connection_speed) {
      GST_DEBUG_OBJECT (dec, "bitrate too high: %" GST_PTR_FORMAT, s);
      l_bad = g_list_append (l_bad, (gpointer) s);
    } else if (bitrate <= dec->connection_speed) {
      GST_DEBUG_OBJECT (dec, "bitrate OK: %" GST_PTR_FORMAT, s);
      l_good = g_list_append (l_good, (gpointer) s);
    }
  }

  g_value_init (&new_list, GST_TYPE_LIST);
  value_list_append_structure_list (&new_list, &new_structure, l_good);
  value_list_append_structure_list (&new_list, &new_structure, l_neutral);
  value_list_append_structure_list (&new_list, &new_structure, l_bad);
  gst_structure_take_value (new_structure, "locations", &new_list);

  g_list_free (l_good);
  g_list_free (l_neutral);
  g_list_free (l_bad);

  new_msg = gst_message_new_element (msg->src, new_structure);
  gst_message_unref (msg);

  GST_DEBUG_OBJECT (dec, "new redirect message: %" GST_PTR_FORMAT, new_msg);
  return new_msg;
}
