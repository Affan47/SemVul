rtp_session_request_key_unit (RTPSession * sess, guint32 ssrc,
    gboolean fir, gint count)
{
  RTPSource *src;

  RTP_SESSION_LOCK (sess);
  src = find_source (sess, ssrc);
  if (!src)
    goto no_source;

  if (fir) {
    src->send_pli = FALSE;
    src->send_fir = TRUE;

    if (count == -1 || count != src->last_fir_count)
      src->current_send_fir_seqnum++;
    src->last_fir_count = count;
  } else if (!src->send_fir) {
    src->send_pli = TRUE;
  }
  RTP_SESSION_UNLOCK (sess);

  rtp_session_send_rtcp (sess, 200 * GST_MSECOND);

  return TRUE;


no_source:
  {
    RTP_SESSION_UNLOCK (sess);
    return FALSE;
  }
}
