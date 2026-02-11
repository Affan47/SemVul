rtp_session_request_early_rtcp (RTPSession * sess, GstClockTime current_time,
    GstClockTimeDiff max_delay)
{
  GstClockTime T_dither_max;


  RTP_SESSION_LOCK (sess);


  if (GST_CLOCK_TIME_IS_VALID (sess->next_early_rtcp_time))
    goto dont_send;


  if (current_time + max_delay > sess->next_rtcp_check_time)
    goto dont_send;


  if (sess->total_sources <= 2) {
    T_dither_max = 0;
  } else {

    T_dither_max = sess->next_rtcp_check_time - sess->last_rtcp_send_time;
    T_dither_max /= 2;
  }


  if (current_time + T_dither_max > sess->next_rtcp_check_time)
    goto dont_send;


  if (sess->total_sources > sess->rtcp_immediate_feedback_threshold &&
      sess->allow_early == FALSE)
    goto dont_send;

  if (T_dither_max) {

    sess->next_early_rtcp_time = g_random_double () * T_dither_max +
        current_time;
  } else {

    sess->next_early_rtcp_time = current_time;
  }

  RTP_SESSION_UNLOCK (sess);


  if (sess->callbacks.reconsider)
    sess->callbacks.reconsider (sess, sess->reconsider_user_data);

  return;

dont_send:

  RTP_SESSION_UNLOCK (sess);
}
