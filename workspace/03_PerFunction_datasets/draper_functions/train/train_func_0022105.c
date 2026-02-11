fs_rtp_session_try_sending_dtmf_event (FsRtpSession *self)
{
  GstElement *rtpmuxer = NULL;
  GstPad *pad;
  gboolean ret = FALSE;
  GstEvent *event;

  FS_RTP_SESSION_LOCK (self);
  if (self->priv->telephony_event_running ||
      g_queue_get_length (&self->priv->telephony_events) == 0)
  {
    FS_RTP_SESSION_UNLOCK (self);
    return;
  }


  g_assert (self->priv->rtpmuxer);
  rtpmuxer = gst_object_ref (self->priv->rtpmuxer);
  FS_RTP_SESSION_UNLOCK (self);

  pad = gst_element_get_static_pad (rtpmuxer, "src");

  event = fs_rtp_session_set_next_telephony_method (self, 1);
  ret = gst_pad_send_event (pad, event);
  if (!ret)
  {
    event = fs_rtp_session_set_next_telephony_method (self, 2);
    ret = gst_pad_send_event (pad, event);
  }

  if (!ret)
  {
    FS_RTP_SESSION_LOCK (self);
    self->priv->telephony_event_running = FALSE;
    FS_RTP_SESSION_UNLOCK (self);
  }

  gst_object_unref (pad);
  gst_object_unref (rtpmuxer);
}
