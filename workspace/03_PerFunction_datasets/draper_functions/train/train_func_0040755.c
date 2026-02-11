gst_mpeg_audio_parse_check_valid_frame (GstBaseParse * parse,
    GstBaseParseFrame * frame, guint * framesize, gint * skipsize)
{
  GstMpegAudioParse *mp3parse = GST_MPEG_AUDIO_PARSE (parse);
  GstBuffer *buf = frame->buffer;
  GstByteReader reader = GST_BYTE_READER_INIT_FROM_BUFFER (buf);
  gint off, bpf;
  gboolean lost_sync, draining, valid, caps_change;
  guint32 header;
  guint bitrate, layer, rate, channels, version, mode, crc;

  if (G_UNLIKELY (GST_BUFFER_SIZE (buf) < 6))
    return FALSE;

  off = gst_byte_reader_masked_scan_uint32 (&reader, 0xffe00000, 0xffe00000,
      0, GST_BUFFER_SIZE (buf));

  GST_LOG_OBJECT (parse, "possible sync at buffer offset %d", off);


  if (off < 0) {
    *skipsize = GST_BUFFER_SIZE (buf) - 3;
    return FALSE;
  }


  if (off > 0) {
    *skipsize = off;
    return FALSE;
  }


  header = GST_READ_UINT32_BE (GST_BUFFER_DATA (buf));
  if (!gst_mpeg_audio_parse_head_check (mp3parse, header)) {
    *skipsize = 1;
    return FALSE;
  }

  GST_LOG_OBJECT (parse, "got frame");

  bpf = mp3_type_frame_length_from_header (mp3parse, header,
      &version, &layer, &channels, &bitrate, &rate, &mode, &crc);
  g_assert (bpf != 0);

  if (channels != mp3parse->channels || rate != mp3parse->rate ||
      layer != mp3parse->layer || version != mp3parse->version)
    caps_change = TRUE;
  else
    caps_change = FALSE;

  lost_sync = GST_BASE_PARSE_LOST_SYNC (parse);
  draining = GST_BASE_PARSE_DRAINING (parse);

  if (!draining && (lost_sync || caps_change)) {
    if (!gst_mp3parse_validate_extended (mp3parse, buf, header, bpf, draining,
            &valid)) {

      gst_base_parse_set_min_frame_size (parse, valid);
      *skipsize = 0;
      return FALSE;
    } else {
      if (!valid) {
        *skipsize = off + 2;
        return FALSE;
      }
    }
  } else if (draining && lost_sync && caps_change && mp3parse->rate > 0) {

    *skipsize = off + 2;
    return FALSE;
  }


  gst_base_parse_set_min_frame_size (parse, MIN_FRAME_SIZE);

  *framesize = bpf;
  return TRUE;
}
