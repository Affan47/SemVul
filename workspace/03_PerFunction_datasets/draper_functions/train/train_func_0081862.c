gst_video_test_src_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstVideoTestSrc *src = GST_VIDEO_TEST_SRC (object);

  switch (prop_id) {
    case PROP_PATTERN:
      g_value_set_enum (value, src->pattern_type);
      break;
    case PROP_TIMESTAMP_OFFSET:
      g_value_set_int64 (value, src->timestamp_offset);
      break;
    case PROP_IS_LIVE:
      g_value_set_boolean (value, gst_base_src_is_live (GST_BASE_SRC (src)));
      break;
    case PROP_K0:
      g_value_set_int (value, src->k0);
      break;
    case PROP_KX:
      g_value_set_int (value, src->kx);
      break;
    case PROP_KY:
      g_value_set_int (value, src->ky);
      break;
    case PROP_KT:
      g_value_set_int (value, src->kt);
      break;
    case PROP_KXT:
      g_value_set_int (value, src->kxt);
      break;
    case PROP_KYT:
      g_value_set_int (value, src->kyt);
      break;
    case PROP_KXY:
      g_value_set_int (value, src->kxy);
      break;
    case PROP_KX2:
      g_value_set_int (value, src->kx2);
      break;
    case PROP_KY2:
      g_value_set_int (value, src->ky2);
      break;
    case PROP_KT2:
      g_value_set_int (value, src->kt2);
      break;
    case PROP_XOFFSET:
      g_value_set_int (value, src->xoffset);
      break;
    case PROP_YOFFSET:
      g_value_set_int (value, src->yoffset);
      break;
    case PROP_FOREGROUND_COLOR:
      g_value_set_uint (value, src->foreground_color);
      break;
    case PROP_BACKGROUND_COLOR:
      g_value_set_uint (value, src->background_color);
      break;
    case PROP_HORIZONTAL_SPEED:
      g_value_set_int (value, src->horizontal_speed);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
