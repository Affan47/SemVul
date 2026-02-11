gst_rtp_g722_depay_setcaps (GstBaseRTPDepayload * depayload, GstCaps * caps)
{
  GstStructure *structure;
  GstRtpG722Depay *rtpg722depay;
  gint clock_rate, payload, samplerate;
  gint channels;
  GstCaps *srccaps;
  gboolean res;
  const gchar *channel_order;
  const GstRTPChannelOrder *order;

  rtpg722depay = GST_RTP_G722_DEPAY (depayload);

  structure = gst_caps_get_structure (caps, 0);

  payload = 96;
  gst_structure_get_int (structure, "payload", &payload);
  switch (payload) {
    case GST_RTP_PAYLOAD_G722:
      channels = 1;
      clock_rate = 8000;
      samplerate = 16000;
      break;
    default:

      channels = 0;
      clock_rate = 0;
      samplerate = 0;
      break;
  }


  clock_rate =
      gst_rtp_g722_depay_parse_int (structure, "clock-rate", clock_rate);
  if (clock_rate == 0)
    goto no_clockrate;

  if (clock_rate == 8000)
    samplerate = 16000;

  if (samplerate == 0)
    samplerate = clock_rate;

  channels =
      gst_rtp_g722_depay_parse_int (structure, "encoding-params", channels);
  if (channels == 0) {
    channels = gst_rtp_g722_depay_parse_int (structure, "channels", channels);
    if (channels == 0) {

      channels = 1;
    }
  }

  depayload->clock_rate = clock_rate;
  rtpg722depay->rate = samplerate;
  rtpg722depay->channels = channels;

  srccaps = gst_caps_new_simple ("audio/G722",
      "rate", G_TYPE_INT, samplerate, "channels", G_TYPE_INT, channels, NULL);


  channel_order = gst_structure_get_string (structure, "channel-order");

  order = gst_rtp_channels_get_by_order (channels, channel_order);
  if (order) {
    gst_audio_set_channel_positions (gst_caps_get_structure (srccaps, 0),
        order->pos);
  } else {
    GstAudioChannelPosition *pos;

    GST_ELEMENT_WARNING (rtpg722depay, STREAM, DECODE,
        (NULL), ("Unknown channel order '%s' for %d channels",
            GST_STR_NULL (channel_order), channels));

    pos = gst_rtp_channels_create_default (channels);
    gst_audio_set_channel_positions (gst_caps_get_structure (srccaps, 0), pos);
    g_free (pos);
  }

  res = gst_pad_set_caps (depayload->srcpad, srccaps);
  gst_caps_unref (srccaps);

  return res;


no_clockrate:
  {
    GST_ERROR_OBJECT (depayload, "no clock-rate specified");
    return FALSE;
  }
}
