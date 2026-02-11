gst_rtp_jitter_buffer_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * name, const GstCaps * filter)
{
  GstRtpJitterBuffer *jitterbuffer;
  GstElementClass *klass;
  GstPad *result;
  GstRtpJitterBufferPrivate *priv;

  g_return_val_if_fail (templ != NULL, NULL);
  g_return_val_if_fail (GST_IS_RTP_JITTER_BUFFER (element), NULL);

  jitterbuffer = GST_RTP_JITTER_BUFFER (element);
  priv = jitterbuffer->priv;
  klass = GST_ELEMENT_GET_CLASS (element);

  GST_DEBUG_OBJECT (element, "requesting pad %s", GST_STR_NULL (name));


  if (templ == gst_element_class_get_pad_template (klass, "sink_rtcp")) {
    if (priv->rtcpsinkpad != NULL)
      goto exists;

    result = create_rtcp_sink (jitterbuffer);
  } else
    goto wrong_template;

  return result;


wrong_template:
  {
    g_warning ("rtpjitterbuffer: this is not our template");
    return NULL;
  }
exists:
  {
    g_warning ("rtpjitterbuffer: pad already requested");
    return NULL;
  }
}
