rtp_session_update_send_caps (RTPSession * sess, GstCaps * caps)
{
  GstStructure *s;
  guint ssrc;

  g_return_if_fail (RTP_IS_SESSION (sess));
  g_return_if_fail (GST_IS_CAPS (caps));

  GST_LOG ("received caps %" GST_PTR_FORMAT, caps);

  s = gst_caps_get_structure (caps, 0);

  if (gst_structure_get_uint (s, "ssrc", &ssrc)) {
    RTPSource *source;
    gboolean created;

    RTP_SESSION_LOCK (sess);
    source = obtain_internal_source (sess, ssrc, &created);
    if (source) {
      rtp_source_update_caps (source, caps);
      g_object_unref (source);
    }
    RTP_SESSION_UNLOCK (sess);
  }
}
