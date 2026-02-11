gst_rtp_g726_pay_setcaps (GstBaseRTPPayload * payload, GstCaps * caps)
{
  gchar *encoding_name;
  GstStructure *structure;
  GstBaseRTPAudioPayload *basertpaudiopayload;
  GstRtpG726Pay *pay;
  GstCaps *peercaps;
  gboolean res;

  basertpaudiopayload = GST_BASE_RTP_AUDIO_PAYLOAD (payload);
  pay = GST_RTP_G726_PAY (payload);

  structure = gst_caps_get_structure (caps, 0);

  if (!gst_structure_get_int (structure, "bitrate", &pay->bitrate))
    pay->bitrate = 32000;

  GST_DEBUG_OBJECT (payload, "using bitrate %d", pay->bitrate);

  pay->aal2 = FALSE;


  switch (pay->bitrate) {
    case 16000:
      encoding_name = g_strdup ("G726-16");
      gst_base_rtp_audio_payload_set_samplebits_options (basertpaudiopayload,
          2);
      break;
    case 24000:
      encoding_name = g_strdup ("G726-24");
      gst_base_rtp_audio_payload_set_samplebits_options (basertpaudiopayload,
          3);
      break;
    case 32000:
      encoding_name = g_strdup ("G726-32");
      gst_base_rtp_audio_payload_set_samplebits_options (basertpaudiopayload,
          4);
      break;
    case 40000:
      encoding_name = g_strdup ("G726-40");
      gst_base_rtp_audio_payload_set_samplebits_options (basertpaudiopayload,
          5);
      break;
    default:
      goto invalid_bitrate;
  }

  GST_DEBUG_OBJECT (payload, "selected base encoding %s", encoding_name);


  peercaps = gst_pad_peer_get_caps (payload->srcpad);
  if (peercaps) {
    GstCaps *filter, *intersect;
    gchar *capsstr;

    GST_DEBUG_OBJECT (payload, "have peercaps %" GST_PTR_FORMAT, peercaps);

    capsstr = g_strdup_printf ("application/x-rtp, "
        "media = (string) \"audio\", "
        "clock-rate = (int) 8000, "
        "encoding-name = (string) %s; "
        "application/x-rtp, "
        "media = (string) \"audio\", "
        "clock-rate = (int) 8000, "
        "encoding-name = (string) AAL2-%s", encoding_name, encoding_name);
    filter = gst_caps_from_string (capsstr);
    g_free (capsstr);


    intersect = gst_caps_intersect (peercaps, filter);
    gst_caps_unref (peercaps);

    GST_DEBUG_OBJECT (payload, "intersected to %" GST_PTR_FORMAT, intersect);

    if (!intersect)
      goto no_format;
    if (gst_caps_is_empty (intersect)) {
      gst_caps_unref (intersect);
      goto no_format;
    }

    structure = gst_caps_get_structure (intersect, 0);


    encoding_name =
        g_strdup (gst_structure_get_string (structure, "encoding-name"));


    if (g_str_has_prefix (encoding_name, "AAL2-"))
      pay->aal2 = TRUE;
    else
      pay->aal2 = pay->force_aal2;

    GST_DEBUG_OBJECT (payload, "final encoding %s, AAL2 %d", encoding_name,
        pay->aal2);

    gst_caps_unref (intersect);
  } else {

    pay->aal2 = pay->force_aal2;
    GST_DEBUG_OBJECT (payload, "no peer caps, AAL2 %d", pay->aal2);
  }

  gst_basertppayload_set_options (payload, "audio", TRUE, encoding_name, 8000);
  res = gst_basertppayload_set_outcaps (payload, NULL);

  g_free (encoding_name);

  return res;


invalid_bitrate:
  {
    GST_ERROR_OBJECT (payload, "invalid bitrate %d specified", pay->bitrate);
    return FALSE;
  }
no_format:
  {
    GST_ERROR_OBJECT (payload, "could not negotiate format");
    return FALSE;
  }
}
