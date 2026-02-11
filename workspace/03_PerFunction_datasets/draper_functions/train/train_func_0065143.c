gst_rtp_mpa_robust_depay_dequeue_frame (GstRtpMPARobustDepay * rtpmpadepay)
{
  GstADUFrame *head;

  GST_LOG_OBJECT (rtpmpadepay, "dequeueing ADU frame");

  if (rtpmpadepay->adu_frames->head == rtpmpadepay->cur_adu_frame)
    rtpmpadepay->cur_adu_frame = NULL;

  head = g_queue_pop_head (rtpmpadepay->adu_frames);
  g_assert (head->buffer);
  gst_rtp_mpa_robust_depay_free_frame (head);

  return;
}
