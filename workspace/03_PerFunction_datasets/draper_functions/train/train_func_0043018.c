gst_rtp_session_request_remote_key_unit (GstRtpSession * rtpsession,
    guint32 ssrc, guint payload, gboolean all_headers, gint count)
{
  GstCaps *caps;

  caps = gst_rtp_session_get_caps_for_pt (rtpsession, payload);

  if (caps) {
    const GstStructure *s = gst_caps_get_structure (caps, 0);
    gboolean pli;
    gboolean fir;

    pli = gst_structure_has_field (s, "rtcp-fb-nack-pli");
    fir = gst_structure_has_field (s, "rtcp-fb-ccm-fir") && all_headers;


    if (!pli &&
        gst_structure_has_field (s, "rtcp-fb-x-gstreamer-fir-as-repair"))
      fir = TRUE;

    gst_caps_unref (caps);

    if (pli || fir)
      return rtp_session_request_key_unit (rtpsession->priv->session, ssrc,
          gst_clock_get_time (rtpsession->priv->sysclock), fir, count);
  }

  return FALSE;
}
