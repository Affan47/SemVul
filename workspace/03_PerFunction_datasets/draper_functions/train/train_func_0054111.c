rtcp_thread (GstRtpSession * rtpsession)
{
  GstClockID id;
  GstClockTime current_time;
  GstClockTime next_timeout;
  guint64 ntpnstime;
  GstClockTime running_time;
  RTPSession *session;
  GstClock *sysclock;

  GST_DEBUG_OBJECT (rtpsession, "entering RTCP thread");

  GST_RTP_SESSION_LOCK (rtpsession);

  sysclock = rtpsession->priv->sysclock;
  current_time = gst_clock_get_time (sysclock);

  session = rtpsession->priv->session;

  GST_DEBUG_OBJECT (rtpsession, "starting at %" GST_TIME_FORMAT,
      GST_TIME_ARGS (current_time));
  session->start_time = current_time;

  while (!rtpsession->priv->stop_thread) {
    GstClockReturn res;


    next_timeout = rtp_session_next_timeout (session, current_time);

    GST_DEBUG_OBJECT (rtpsession, "next check time %" GST_TIME_FORMAT,
        GST_TIME_ARGS (next_timeout));


    if (next_timeout == GST_CLOCK_TIME_NONE)
      break;

    id = rtpsession->priv->id =
        gst_clock_new_single_shot_id (sysclock, next_timeout);
    GST_RTP_SESSION_UNLOCK (rtpsession);

    res = gst_clock_id_wait (id, NULL);

    GST_RTP_SESSION_LOCK (rtpsession);
    gst_clock_id_unref (id);
    rtpsession->priv->id = NULL;

    if (rtpsession->priv->stop_thread)
      break;


    current_time = gst_clock_get_time (sysclock);


    get_current_times (rtpsession, &running_time, &ntpnstime);


    GST_DEBUG_OBJECT (rtpsession, "unlocked %d, current %" GST_TIME_FORMAT,
        res, GST_TIME_ARGS (current_time));


    GST_RTP_SESSION_UNLOCK (rtpsession);
    rtp_session_on_timeout (session, current_time, ntpnstime, running_time);
    GST_RTP_SESSION_LOCK (rtpsession);
  }

  rtpsession->priv->thread_stopped = TRUE;
  GST_RTP_SESSION_UNLOCK (rtpsession);

  GST_DEBUG_OBJECT (rtpsession, "leaving RTCP thread");
}
