gst_message_new_tag_full (GstObject * src, GstPad * pad, GstTagList * tag_list)
{
  GstMessage *message;
  GstStructure *s;

  g_return_val_if_fail (GST_IS_STRUCTURE (tag_list), NULL);
  g_return_val_if_fail (pad == NULL || GST_IS_PAD (pad), NULL);

  s = (GstStructure *) tag_list;
  if (pad)
    gst_structure_set (s, "source-pad", GST_TYPE_PAD, pad, NULL);

  message = gst_message_new_custom (GST_MESSAGE_TAG, src, s);

  return message;
}
