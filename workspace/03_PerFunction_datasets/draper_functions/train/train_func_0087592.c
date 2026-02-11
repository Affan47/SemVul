gst_mpeg_audio_parse_head_check (GstMpegAudioParse * mp3parse,
    unsigned long head)
{
  GST_DEBUG_OBJECT (mp3parse, "checking mp3 header 0x%08lx", head);

  if ((head & 0xffe00000) != 0xffe00000) {
    GST_WARNING_OBJECT (mp3parse, "invalid sync");
    return FALSE;
  }

  if (((head >> 19) & 3) == 0x1) {
    GST_WARNING_OBJECT (mp3parse, "invalid MPEG version: 0x%lx",
        (head >> 19) & 3);
    return FALSE;
  }

  if (!((head >> 17) & 3)) {
    GST_WARNING_OBJECT (mp3parse, "invalid layer: 0x%lx", (head >> 17) & 3);
    return FALSE;
  }

  if (((head >> 12) & 0xf) == 0xf) {
    GST_WARNING_OBJECT (mp3parse, "invalid bitrate: 0x%lx", (head >> 12) & 0xf);
    return FALSE;
  }

  if (((head >> 10) & 0x3) == 0x3) {
    GST_WARNING_OBJECT (mp3parse, "invalid samplerate: 0x%lx",
        (head >> 10) & 0x3);
    return FALSE;
  }

  if ((head & 0x3) == 0x2) {


    GST_WARNING_OBJECT (mp3parse, "invalid emphasis: 0x%lx", head & 0x3);
  }

  return TRUE;
}
