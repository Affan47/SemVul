gnl_object_to_media_time (GnlObject * object, GstClockTime otime,
    GstClockTime * mtime)
{
  g_return_val_if_fail (mtime, FALSE);

  GST_DEBUG_OBJECT (object, "ObjectTime : %" GST_TIME_FORMAT,
      GST_TIME_ARGS (otime));

  GST_DEBUG_OBJECT (object,
      "Start/Stop:[%" GST_TIME_FORMAT " -- %" GST_TIME_FORMAT "] "
      "Media [%" GST_TIME_FORMAT " -- %" GST_TIME_FORMAT "]",
      GST_TIME_ARGS (object->start),
      GST_TIME_ARGS (object->stop),
      GST_TIME_ARGS (object->media_start), GST_TIME_ARGS (object->media_stop));


  if (G_UNLIKELY ((otime < object->start))) {
    GST_DEBUG_OBJECT (object, "ObjectTime is before start");
    *mtime =
        (object->media_start == GST_CLOCK_TIME_NONE) ? 0 : object->media_start;
    return FALSE;
  }
  if (G_UNLIKELY ((otime >= object->stop))) {
    GST_DEBUG_OBJECT (object, "ObjectTime is after stop");
    if (G_LIKELY (GST_CLOCK_TIME_IS_VALID (object->media_stop)))
      *mtime = object->media_stop;
    else if (GST_CLOCK_TIME_IS_VALID (object->media_start))
      *mtime = object->media_start + object->duration;
    else
      *mtime = object->stop - object->start;
    return FALSE;
  }

  if (G_UNLIKELY (object->media_start == GST_CLOCK_TIME_NONE)) {

    *mtime = otime - object->start;
  } else if (G_LIKELY (object->rate_1)) {
    *mtime = otime - object->start + object->media_start;
  } else {
    *mtime = (otime - object->start) * object->rate + object->media_start;
  }

  GST_DEBUG_OBJECT (object, "Returning MediaTime : %" GST_TIME_FORMAT,
      GST_TIME_ARGS (*mtime));

  return TRUE;
}
