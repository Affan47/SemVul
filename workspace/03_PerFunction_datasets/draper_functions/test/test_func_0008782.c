gst_mpeg_audio_parse_parse_frame (GstBaseParse * parse,
    GstBaseParseFrame * frame)
{
  GstMpegAudioParse *mp3parse = GST_MPEG_AUDIO_PARSE (parse);
  GstBuffer *buf = frame->buffer;
  guint bitrate, layer, rate, channels, version, mode, crc;

  g_return_val_if_fail (GST_BUFFER_SIZE (buf) >= 4, GST_FLOW_ERROR);

  if (!mp3_type_frame_length_from_header (mp3parse,
          GST_READ_UINT32_BE (GST_BUFFER_DATA (buf)),
          &version, &layer, &channels, &bitrate, &rate, &mode, &crc))
    goto broken_header;

  if (G_UNLIKELY (channels != mp3parse->channels || rate != mp3parse->rate ||
          layer != mp3parse->layer || version != mp3parse->version)) {
    GstCaps *caps = gst_caps_new_simple ("audio/mpeg",
        "mpegversion", G_TYPE_INT, 1,
        "mpegaudioversion", G_TYPE_INT, version,
        "layer", G_TYPE_INT, layer,
        "rate", G_TYPE_INT, rate,
        "channels", G_TYPE_INT, channels, "parsed", G_TYPE_BOOLEAN, TRUE, NULL);
    gst_buffer_set_caps (buf, caps);
    gst_pad_set_caps (GST_BASE_PARSE_SRC_PAD (parse), caps);
    gst_caps_unref (caps);

    mp3parse->rate = rate;
    mp3parse->channels = channels;
    mp3parse->layer = layer;
    mp3parse->version = version;


    if (mp3parse->layer == 1)
      mp3parse->spf = 384;
    else if (mp3parse->layer == 2)
      mp3parse->spf = 1152;
    else if (mp3parse->version == 1) {
      mp3parse->spf = 1152;
    } else {

      mp3parse->spf = 576;
    }


    gst_base_parse_set_frame_rate (parse, mp3parse->rate, mp3parse->spf,
        (version == 1) ? 10 : 30, 2);
  }

  mp3parse->hdr_bitrate = bitrate;


  gst_mpeg_audio_parse_handle_first_frame (mp3parse, buf);


  mp3parse->last_crc = crc;
  mp3parse->last_mode = mode;

  return GST_FLOW_OK;


broken_header:
  {

    GST_ELEMENT_ERROR (parse, STREAM, DECODE, (NULL), (NULL));
    return GST_FLOW_ERROR;
  }
}
