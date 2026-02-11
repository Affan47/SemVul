gst_stream_info_get_property (GObject * object, guint prop_id, GValue * value,
    GParamSpec * pspec)
{
  GstStreamInfo *stream_info;

  g_return_if_fail (GST_IS_STREAM_INFO (object));

  stream_info = GST_STREAM_INFO (object);

  switch (prop_id) {
    case ARG_PAD:
      g_value_set_object (value, stream_info->object);
      break;
    case ARG_TYPE:
      g_value_set_enum (value, stream_info->type);
      break;
    case ARG_DECODER:
      g_value_set_string (value, stream_info->decoder);
      break;
    case ARG_MUTE:
      g_value_set_boolean (value, stream_info->mute);
      break;
    case ARG_CAPS:
      g_value_set_boxed (value, stream_info->caps);
      break;
    case ARG_LANG_CODE:
      g_value_set_string (value, stream_info->langcode);
      break;
    case ARG_CODEC:
      g_value_set_string (value, stream_info->codec);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
