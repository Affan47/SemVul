gst_video_median_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstVideoMedian *median;

  median = GST_VIDEO_MEDIAN (object);

  switch (prop_id) {
    case PROP_FILTERSIZE:
      median->filtersize = g_value_get_enum (value);
      break;
    case PROP_LUM_ONLY:
      median->lum_only = g_value_get_boolean (value);
      break;
    default:
      break;
  }
}
