rtp_session_request_local_key_unit (RTPSession * sess, RTPSource * src,
    gboolean fir, GstClockTime current_time)
{
  guint32 round_trip = 0;

  rtp_source_get_last_rb (src, NULL, NULL, NULL, NULL, NULL, NULL, &round_trip);

  if (sess->last_keyframe_request != GST_CLOCK_TIME_NONE && round_trip) {
    GstClockTime round_trip_in_ns = gst_util_uint64_scale (round_trip,
        GST_SECOND, 65536);

    if (current_time - sess->last_keyframe_request < 2 * round_trip_in_ns) {
      GST_DEBUG ("Ignoring %s request because one was send without one "
          "RTT (%" GST_TIME_FORMAT " < %" GST_TIME_FORMAT ")",
          fir ? "FIR" : "PLI",
          GST_TIME_ARGS (current_time - sess->last_keyframe_request),
          GST_TIME_ARGS (round_trip_in_ns));;
      return FALSE;
    }
  }

  sess->last_keyframe_request = current_time;

  GST_LOG ("received %s request from %X %p(%p)", fir ? "FIR" : "PLI",
      rtp_source_get_ssrc (src), sess->callbacks.process_rtp,
      sess->callbacks.request_key_unit);

  RTP_SESSION_UNLOCK (sess);
  sess->callbacks.request_key_unit (sess, fir,
      sess->request_key_unit_user_data);
  RTP_SESSION_LOCK (sess);

  return TRUE;
}
