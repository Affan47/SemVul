composition_duration_cb (GstElement * composition,
    GParamSpec * arg G_GNUC_UNUSED, GESTrack * track)
{
  guint64 duration;

  g_object_get (composition, "duration", &duration, NULL);

  if (track->priv->duration != duration) {
    GST_DEBUG_OBJECT (track,
        "composition duration : %" GST_TIME_FORMAT " current : %"
        GST_TIME_FORMAT, GST_TIME_ARGS (duration),
        GST_TIME_ARGS (track->priv->duration));

    track->priv->duration = duration;

    g_object_notify_by_pspec (G_OBJECT (track), properties[ARG_DURATION]);
  }
}
