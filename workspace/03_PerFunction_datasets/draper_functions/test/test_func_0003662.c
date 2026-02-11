gst_rtp_h264_depay_finalize (GObject * object)
{
  GstRtpH264Depay *rtph264depay;

  rtph264depay = GST_RTP_H264_DEPAY (object);

  if (rtph264depay->codec_data)
    gst_buffer_unref (rtph264depay->codec_data);

  g_object_unref (rtph264depay->adapter);
  g_object_unref (rtph264depay->picture_adapter);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
