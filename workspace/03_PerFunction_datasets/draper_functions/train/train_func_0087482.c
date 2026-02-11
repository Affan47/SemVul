gst_rtp_session_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * name)
{
  GstRtpSession *rtpsession;
  GstElementClass *klass;
  GstPad *result;

  g_return_val_if_fail (templ != NULL, NULL);
  g_return_val_if_fail (GST_IS_RTP_SESSION (element), NULL);

  rtpsession = GST_RTP_SESSION (element);
  klass = GST_ELEMENT_GET_CLASS (element);

  GST_DEBUG_OBJECT (element, "requesting pad %s", GST_STR_NULL (name));

  GST_RTP_SESSION_LOCK (rtpsession);


  if (templ == gst_element_class_get_pad_template (klass, "recv_rtp_sink")) {
    if (rtpsession->recv_rtp_sink != NULL)
      goto exists;

    result = create_recv_rtp_sink (rtpsession);
  } else if (templ == gst_element_class_get_pad_template (klass,
          "recv_rtcp_sink")) {
    if (rtpsession->recv_rtcp_sink != NULL)
      goto exists;

    result = create_recv_rtcp_sink (rtpsession);
  } else if (templ == gst_element_class_get_pad_template (klass,
          "send_rtp_sink")) {
    if (rtpsession->send_rtp_sink != NULL)
      goto exists;

    result = create_send_rtp_sink (rtpsession);
  } else if (templ == gst_element_class_get_pad_template (klass,
          "send_rtcp_src")) {
    if (rtpsession->send_rtcp_src != NULL)
      goto exists;

    result = create_send_rtcp_src (rtpsession);
  } else
    goto wrong_template;

  GST_RTP_SESSION_UNLOCK (rtpsession);

  return result;


wrong_template:
  {
    GST_RTP_SESSION_UNLOCK (rtpsession);
    g_warning ("gstrtpsession: this is not our template");
    return NULL;
  }
exists:
  {
    GST_RTP_SESSION_UNLOCK (rtpsession);
    g_warning ("gstrtpsession: pad already requested");
    return NULL;
  }
}
