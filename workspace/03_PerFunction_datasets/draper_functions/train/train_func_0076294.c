gst_rtp_g723_pay_flush (GstRTPG723Pay * pay)
{
  GstBuffer *outbuf;
  GstFlowReturn ret;
  guint8 *payload;
  guint avail;
  GstRTPBuffer rtp = { NULL };

  avail = gst_adapter_available (pay->adapter);

  outbuf = gst_rtp_buffer_new_allocate (avail, 0, 0);

  gst_rtp_buffer_map (outbuf, GST_MAP_WRITE, &rtp);
  payload = gst_rtp_buffer_get_payload (&rtp);

  GST_BUFFER_TIMESTAMP (outbuf) = pay->timestamp;
  GST_BUFFER_DURATION (outbuf) = pay->duration;


  gst_adapter_copy (pay->adapter, payload, 0, avail);


  gst_adapter_flush (pay->adapter, avail);
  pay->timestamp = GST_CLOCK_TIME_NONE;
  pay->duration = 0;


  if (pay->discont) {
    GST_BUFFER_FLAG_SET (outbuf, GST_BUFFER_FLAG_DISCONT);
    gst_rtp_buffer_set_marker (&rtp, TRUE);
    pay->discont = FALSE;
  }
  gst_rtp_buffer_unmap (&rtp);

  ret = gst_rtp_base_payload_push (GST_RTP_BASE_PAYLOAD (pay), outbuf);

  return ret;
}
