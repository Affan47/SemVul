gst_rtp_asf_pay_parse_headers (GstRtpAsfPay * rtpasfpay)
{
  gchar *maxps;
  g_return_val_if_fail (rtpasfpay->headers, GST_FLOW_ERROR);

  if (!gst_asf_parse_headers (rtpasfpay->headers, &rtpasfpay->asfinfo))
    goto error;

  GST_DEBUG_OBJECT (rtpasfpay, "Packets number: %" G_GUINT64_FORMAT,
      rtpasfpay->asfinfo.packets_count);
  GST_DEBUG_OBJECT (rtpasfpay, "Packets size: %" G_GUINT32_FORMAT,
      rtpasfpay->asfinfo.packet_size);
  GST_DEBUG_OBJECT (rtpasfpay, "Broadcast mode: %s",
      rtpasfpay->asfinfo.broadcast ? "true" : "false");


  g_free (rtpasfpay->config);
  rtpasfpay->config = g_base64_encode (GST_BUFFER_DATA (rtpasfpay->headers),
      GST_BUFFER_SIZE (rtpasfpay->headers));
  GST_DEBUG_OBJECT (rtpasfpay, "Serialized headers to base64 string %s",
      rtpasfpay->config);

  g_assert (rtpasfpay->config != NULL);
  GST_DEBUG_OBJECT (rtpasfpay, "Setting optional caps values: maxps=%"
      G_GUINT32_FORMAT " and config=%s", rtpasfpay->asfinfo.packet_size,
      rtpasfpay->config);
  maxps =
      g_strdup_printf ("%" G_GUINT32_FORMAT, rtpasfpay->asfinfo.packet_size);
  gst_basertppayload_set_outcaps (GST_BASE_RTP_PAYLOAD (rtpasfpay), "maxps",
      G_TYPE_STRING, maxps, "config", G_TYPE_STRING, rtpasfpay->config, NULL);
  g_free (maxps);

  return GST_FLOW_OK;

error:
  {
    GST_ELEMENT_ERROR (rtpasfpay, STREAM, DECODE, (NULL),
        ("Error parsing headers"));
    return GST_FLOW_ERROR;
  }
}
