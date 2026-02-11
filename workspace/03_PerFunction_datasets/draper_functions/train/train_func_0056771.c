bin_do_stream_start (GstBin * bin)
{
  guint32 seqnum = 0;
  gboolean stream_start;
  gboolean have_group_id = FALSE;
  guint group_id = 0;

  GST_OBJECT_LOCK (bin);


  stream_start = is_stream_start (bin, &seqnum, &have_group_id, &group_id);
  GST_OBJECT_UNLOCK (bin);

  if (stream_start) {
    GstMessage *tmessage;

    GST_OBJECT_LOCK (bin);
    bin_remove_messages (bin, NULL, GST_MESSAGE_STREAM_START);
    GST_OBJECT_UNLOCK (bin);

    tmessage = gst_message_new_stream_start (GST_OBJECT_CAST (bin));
    gst_message_set_seqnum (tmessage, seqnum);
    if (have_group_id)
      gst_message_set_group_id (tmessage, group_id);

    GST_DEBUG_OBJECT (bin,
        "all sinks posted STREAM_START, posting seqnum #%" G_GUINT32_FORMAT,
        seqnum);
    gst_element_post_message (GST_ELEMENT_CAST (bin), tmessage);
  }
}
