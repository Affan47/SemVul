_gst_message_free (GstMessage * message)
{
  GstStructure *structure;

  g_return_if_fail (message != NULL);

  GST_CAT_LOG (GST_CAT_MESSAGE, "finalize message %p, %s from %s", message,
      GST_MESSAGE_TYPE_NAME (message), GST_MESSAGE_SRC_NAME (message));

  if (GST_MESSAGE_SRC (message)) {
    gst_object_unref (GST_MESSAGE_SRC (message));
    GST_MESSAGE_SRC (message) = NULL;
  }

  if (message->lock.p) {
    GST_MESSAGE_LOCK (message);
    GST_MESSAGE_SIGNAL (message);
    GST_MESSAGE_UNLOCK (message);
  }

  structure = GST_MESSAGE_STRUCTURE (message);
  if (structure) {
    gst_structure_set_parent_refcount (structure, NULL);
    gst_structure_free (structure);
  }

  g_slice_free1 (sizeof (GstMessageImpl), message);
}
