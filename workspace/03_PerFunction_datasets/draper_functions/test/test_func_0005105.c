calculate_packet_spacing (GstRtpJitterBuffer * jitterbuffer, guint32 rtptime,
    GstClockTime dts)
{
  GstRtpJitterBufferPrivate *priv = jitterbuffer->priv;


  if (priv->ips_rtptime != rtptime) {

    if (priv->ips_dts != -1 && dts != -1 && dts > priv->ips_dts) {
      priv->packet_spacing = dts - priv->ips_dts;
      GST_DEBUG_OBJECT (jitterbuffer,
          "new packet spacing %" GST_TIME_FORMAT,
          GST_TIME_ARGS (priv->packet_spacing));
    }
    priv->ips_rtptime = rtptime;
    priv->ips_dts = dts;
  }
}
