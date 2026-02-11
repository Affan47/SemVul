gst_video_rate_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec)
{
  GstVideoRate *videorate = GST_VIDEO_RATE (object);

  GST_OBJECT_LOCK (videorate);
  switch (prop_id) {
    case PROP_IN:
      g_value_set_uint64 (value, videorate->in);
      break;
    case PROP_OUT:
      g_value_set_uint64 (value, videorate->out);
      break;
    case PROP_DUP:
      g_value_set_uint64 (value, videorate->dup);
      break;
    case PROP_DROP:
      g_value_set_uint64 (value, videorate->drop);
      break;
    case PROP_SILENT:
      g_value_set_boolean (value, videorate->silent);
      break;
    case PROP_NEW_PREF:
      g_value_set_double (value, videorate->new_pref);
      break;
    case PROP_SKIP_TO_FIRST:
      g_value_set_boolean (value, videorate->skip_to_first);
      break;
    case PROP_DROP_ONLY:
      g_value_set_boolean (value, videorate->drop_only);
      break;
    case PROP_AVERAGE_PERIOD:
      g_value_set_uint64 (value, videorate->average_period_set);
      break;
    case PROP_MAX_RATE:
      g_value_set_int (value, g_atomic_int_get (&videorate->max_rate));
      break;
    case PROP_FORCE_FPS:
      gst_value_set_fraction (value, videorate->force_fps_n,
          videorate->force_fps_d);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (videorate);
}
