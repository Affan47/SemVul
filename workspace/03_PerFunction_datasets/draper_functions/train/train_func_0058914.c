gst_mpeg_audio_parse_class_init (GstMpegAudioParseClass * klass)
{
  GstBaseParseClass *parse_class = GST_BASE_PARSE_CLASS (klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  GST_DEBUG_CATEGORY_INIT (mpeg_audio_parse_debug, "mpegaudioparse", 0,
      "MPEG1 audio stream parser");

  object_class->finalize = gst_mpeg_audio_parse_finalize;

  parse_class->start = GST_DEBUG_FUNCPTR (gst_mpeg_audio_parse_start);
  parse_class->stop = GST_DEBUG_FUNCPTR (gst_mpeg_audio_parse_stop);
  parse_class->handle_frame =
      GST_DEBUG_FUNCPTR (gst_mpeg_audio_parse_handle_frame);
  parse_class->pre_push_frame =
      GST_DEBUG_FUNCPTR (gst_mpeg_audio_parse_pre_push_frame);
  parse_class->convert = GST_DEBUG_FUNCPTR (gst_mpeg_audio_parse_convert);
  parse_class->get_sink_caps =
      GST_DEBUG_FUNCPTR (gst_mpeg_audio_parse_get_sink_caps);


#define GST_TAG_CRC      "has-crc"
#define GST_TAG_MODE     "channel-mode"

  gst_tag_register (GST_TAG_CRC, GST_TAG_FLAG_META, G_TYPE_BOOLEAN,
      "has crc", "Using CRC", NULL);
  gst_tag_register (GST_TAG_MODE, GST_TAG_FLAG_ENCODED, G_TYPE_STRING,
      "channel mode", "MPEG audio channel mode", NULL);

  g_type_class_ref (GST_TYPE_MPEG_AUDIO_CHANNEL_MODE);

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&sink_template));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&src_template));

  gst_element_class_set_static_metadata (element_class, "MPEG1 Audio Parser",
      "Codec/Parser/Audio",
      "Parses and frames mpeg1 audio streams (levels 1-3), provides seek",
      "Jan Schmidt <thaytan@mad.scientist.com>,"
      "Mark Nauwelaerts <mark.nauwelaerts@collabora.co.uk>");
}
