gst_mp3parse_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstMPEGAudioParse *src;

  src = GST_MP3PARSE (object);

  switch (prop_id) {
    case ARG_SKIP:
      src->skip = g_value_get_int (value);
      break;
    default:
      break;
  }
}
