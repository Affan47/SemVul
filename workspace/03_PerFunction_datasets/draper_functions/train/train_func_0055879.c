gst_message_new_need_context (GstObject * src, const gchar * context_type)
{
  GstMessage *message;
  GstStructure *structure;

  g_return_val_if_fail (context_type != NULL, NULL);

  structure = gst_structure_new_id (GST_QUARK (MESSAGE_NEED_CONTEXT),
      GST_QUARK (CONTEXT_TYPE), G_TYPE_STRING, context_type, NULL);
  message = gst_message_new_custom (GST_MESSAGE_NEED_CONTEXT, src, structure);

  return message;
}
