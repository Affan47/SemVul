do_expected_timeout (GstRtpJitterBuffer * jitterbuffer, TimerData * timer,
    GstClockTime now)
{
  GstRtpJitterBufferPrivate *priv = jitterbuffer->priv;
  GstEvent *event;
  guint delay;

  GST_DEBUG_OBJECT (jitterbuffer, "expected %d didn't arrive", timer->seqnum);

  delay = timer->rtx_delay + timer->rtx_retry;
  event = gst_event_new_custom (GST_EVENT_CUSTOM_UPSTREAM,
      gst_structure_new ("GstRTPRetransmissionRequest",
          "seqnum", G_TYPE_UINT, (guint) timer->seqnum,
          "running-time", G_TYPE_UINT64, timer->rtx_base,
          "delay", G_TYPE_UINT, GST_TIME_AS_MSECONDS (delay),
          "retry", G_TYPE_UINT, timer->num_rtx_retry,
          "frequency", G_TYPE_UINT, priv->rtx_retry_timeout,
          "period", G_TYPE_UINT, priv->rtx_retry_period,
          "deadline", G_TYPE_UINT, priv->latency_ms,
          "packet-spacing", G_TYPE_UINT64, priv->packet_spacing, NULL));

  priv->num_rtx_requests++;
  timer->num_rtx_retry++;
  timer->rtx_last = now;


  timer->rtx_retry += (priv->rtx_retry_timeout * GST_MSECOND);
  GST_DEBUG_OBJECT (jitterbuffer, "base %" GST_TIME_FORMAT ", delay %"
      GST_TIME_FORMAT ", retry %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timer->rtx_base), GST_TIME_ARGS (timer->rtx_delay),
      GST_TIME_ARGS (timer->rtx_retry));

  if (timer->rtx_retry + timer->rtx_delay >
      (priv->rtx_retry_period * GST_MSECOND)) {
    GST_DEBUG_OBJECT (jitterbuffer, "reschedule as LOST timer");


    timer->type = TIMER_TYPE_LOST;
    timer->rtx_delay = 0;
    timer->rtx_retry = 0;
  }
  reschedule_timer (jitterbuffer, timer, timer->seqnum,
      timer->rtx_base + timer->rtx_retry, timer->rtx_delay, FALSE);

  JBUF_UNLOCK (priv);
  gst_pad_push_event (priv->sinkpad, event);
  JBUF_LOCK (priv);

  return FALSE;
}
