fs_rtp_session_stop_telephony_event (FsSession *session)
{
  FsRtpSession *self = FS_RTP_SESSION (session);
  gboolean ret = FALSE;

  if (fs_rtp_session_has_disposed_enter (self, NULL))
    return FALSE;


  FS_RTP_SESSION_LOCK (self);

  if (!fs_rtp_session_check_telephony_event_queue_start_locked (self, TRUE))
  {
    GST_WARNING ("Tried to stop a telephony event without starting one first");
    goto out;
  }

  GST_DEBUG ("stopping telephony event");

  g_queue_push_head (&self->priv->telephony_events,
      gst_event_new_custom (GST_EVENT_CUSTOM_UPSTREAM,
          gst_structure_new ("dtmf-event",
              "start", G_TYPE_BOOLEAN, FALSE,
              "type", G_TYPE_INT, 1,
              NULL)));

  ret = TRUE;

out:
  FS_RTP_SESSION_UNLOCK (self);

  if (ret)
    fs_rtp_session_try_sending_dtmf_event (self);

  fs_rtp_session_has_disposed_exit (self);
  return ret;
}
