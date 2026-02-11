update_values (GnlObject * object)
{

  if ((object->start + object->duration) != object->stop) {
    object->stop = object->start + object->duration;
    GST_LOG_OBJECT (object,
        "Updating stop value : %" GST_TIME_FORMAT " [start:%" GST_TIME_FORMAT
        ", duration:%" GST_TIME_FORMAT "]", GST_TIME_ARGS (object->stop),
        GST_TIME_ARGS (object->start), GST_TIME_ARGS (object->duration));
#if GLIB_CHECK_VERSION(2,26,0)
    g_object_notify_by_pspec (G_OBJECT (object), properties[PROP_STOP]);
#else
    g_object_notify (G_OBJECT (object), "stop");
#endif
  }


  if ((object->media_start != GST_CLOCK_TIME_NONE)
      && ((object->media_start + object->media_duration) != object->media_stop)) {
    object->media_stop = object->media_start + object->media_duration;
    GST_LOG_OBJECT (object,
        "Updated media_stop value : %" GST_TIME_FORMAT
        " [mstart:%" GST_TIME_FORMAT ", mduration:%" GST_TIME_FORMAT "]",
        GST_TIME_ARGS (object->media_stop),
        GST_TIME_ARGS (object->media_start),
        GST_TIME_ARGS (object->media_duration));
#if GLIB_CHECK_VERSION(2,26,0)
    g_object_notify_by_pspec (G_OBJECT (object), properties[PROP_MEDIA_STOP]);
#else
    g_object_notify (G_OBJECT (object), "media_stop");
#endif
  }


  if ((object->media_duration != GST_CLOCK_TIME_NONE)
      && (object->duration)
      && (object->media_duration)
      && (((gdouble) object->media_duration / (gdouble) object->duration) !=
          object->rate)) {
    object->rate =
        (gdouble) object->media_duration / (gdouble) object->duration;

    object->rate_1 = (object->media_duration == object->duration);
    GST_LOG_OBJECT (object,
        "Updated rate : %f [mduration:%" GST_TIME_FORMAT ", duration:%"
        GST_TIME_FORMAT "] rate_1:%d", object->rate,
        GST_TIME_ARGS (object->media_duration),
        GST_TIME_ARGS (object->duration), object->rate_1);
#if GLIB_CHECK_VERSION(2,26,0)
    g_object_notify_by_pspec (G_OBJECT (object), properties[PROP_RATE]);
#else
    g_object_notify (G_OBJECT (object), "rate");
#endif
  }
}
