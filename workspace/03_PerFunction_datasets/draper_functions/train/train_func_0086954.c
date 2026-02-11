gst_play_bin_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstPlayBin *playbin = GST_PLAY_BIN (object);

  switch (prop_id) {
    case PROP_URI:
      gst_play_bin_set_uri (playbin, g_value_get_string (value));
      break;
    case PROP_SUBURI:
      gst_play_bin_set_suburi (playbin, g_value_get_string (value));
      break;
    case PROP_FLAGS:
      gst_play_bin_set_flags (playbin, g_value_get_flags (value));
      break;
    case PROP_CURRENT_VIDEO:
      gst_play_bin_set_current_video_stream (playbin, g_value_get_int (value));
      break;
    case PROP_CURRENT_AUDIO:
      gst_play_bin_set_current_audio_stream (playbin, g_value_get_int (value));
      break;
    case PROP_CURRENT_TEXT:
      gst_play_bin_set_current_text_stream (playbin, g_value_get_int (value));
      break;
    case PROP_SUBTITLE_ENCODING:
      gst_play_bin_set_encoding (playbin, g_value_get_string (value));
      break;
    case PROP_VIDEO_SINK:
      gst_play_bin_set_sink (playbin, &playbin->video_sink, "video",
          g_value_get_object (value));
      break;
    case PROP_AUDIO_SINK:
      gst_play_bin_set_sink (playbin, &playbin->audio_sink, "audio",
          g_value_get_object (value));
      break;
    case PROP_VIS_PLUGIN:
      gst_play_sink_set_vis_plugin (playbin->playsink,
          g_value_get_object (value));
      break;
    case PROP_TEXT_SINK:
      gst_play_bin_set_sink (playbin, &playbin->text_sink, "text",
          g_value_get_object (value));
      break;
    case PROP_VOLUME:
      gst_play_sink_set_volume (playbin->playsink, g_value_get_double (value));
      break;
    case PROP_MUTE:
      gst_play_sink_set_mute (playbin->playsink, g_value_get_boolean (value));
      break;
    case PROP_FONT_DESC:
      gst_play_sink_set_font_desc (playbin->playsink,
          g_value_get_string (value));
      break;
    case PROP_CONNECTION_SPEED:
      GST_PLAY_BIN_LOCK (playbin);
      playbin->connection_speed = g_value_get_uint (value) * 1000;
      GST_PLAY_BIN_UNLOCK (playbin);
      break;
    case PROP_BUFFER_SIZE:
      playbin->buffer_size = g_value_get_int (value);
      break;
    case PROP_BUFFER_DURATION:
      playbin->buffer_duration = g_value_get_int64 (value);
      break;
    case PROP_AV_OFFSET:
      gst_play_sink_set_av_offset (playbin->playsink,
          g_value_get_int64 (value));
      break;
    case PROP_RING_BUFFER_MAX_SIZE:
      playbin->ring_buffer_max_size = g_value_get_uint64 (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
