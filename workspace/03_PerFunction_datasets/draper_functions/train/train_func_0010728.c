fs_rtp_tfrc_get_sync_time (FsRtpPacketModder *modder,
    GstBuffer *buffer, gpointer user_data)
{
  FsRtpTfrc *self = FS_RTP_TFRC (user_data);
  GstClockTime sync_time = GST_BUFFER_TIMESTAMP (buffer);
  gint bytes_for_one_rtt = 0;
  guint size = 0;
  guint send_rate;

  GST_OBJECT_LOCK (self);

  if (self->extension_type == EXTENSION_NONE || !self->sending)
  {
    GST_OBJECT_UNLOCK (self);
    return GST_CLOCK_TIME_NONE;
  }

  if (self->last_src && self->last_src->sender)
  {
    send_rate = tfrc_sender_get_send_rate (self->last_src->sender);
    bytes_for_one_rtt = send_rate *
        tfrc_sender_get_averaged_rtt (self->last_src->sender);
  }
  else
  {
    send_rate = tfrc_sender_get_send_rate (NULL);
    bytes_for_one_rtt = 0;
  }

  size = gst_buffer_get_size (buffer) + 10;

  if (GST_BUFFER_TIMESTAMP_IS_VALID (buffer))
  {
    if (GST_CLOCK_TIME_IS_VALID (self->last_sent_ts) &&
        self->last_sent_ts < GST_BUFFER_TIMESTAMP (buffer))
      self->byte_reservoir +=
        gst_util_uint64_scale (
            (GST_BUFFER_TIMESTAMP (buffer) - self->last_sent_ts),
            send_rate,
            GST_SECOND);
    self->last_sent_ts = GST_BUFFER_TIMESTAMP (buffer);

    if (bytes_for_one_rtt &&
        self->byte_reservoir > bytes_for_one_rtt)
      self->byte_reservoir = bytes_for_one_rtt;
  }

  self->byte_reservoir -= size;

  if (GST_BUFFER_TIMESTAMP_IS_VALID (buffer) &&
      self->byte_reservoir < 0)
  {
    GstClockTimeDiff diff = 0;

    diff = gst_util_uint64_scale_int (GST_SECOND,
        -self->byte_reservoir, send_rate);
    g_assert (diff > 0);


    GST_LOG_OBJECT (self, "Delaying packet by %"GST_TIME_FORMAT
        " = 1sec * bytes %d / rate %u",
        GST_TIME_ARGS (diff), self->byte_reservoir,
        send_rate);

    GST_BUFFER_TIMESTAMP (buffer) += diff;
  }

  GST_OBJECT_UNLOCK (self);


  return sync_time;
}
