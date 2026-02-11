query_duration (ClutterGstPlayer *player)
{
  ClutterGstPlayerPrivate *priv = PLAYER_GET_PRIVATE (player);
  gboolean success;
  gint64 duration;
  gdouble new_duration, difference;

  success = gst_element_query_duration (priv->pipeline,
                                        GST_FORMAT_TIME,
                                        &duration);
  if (G_UNLIKELY (success != TRUE))
    return;

  new_duration = (gdouble) duration / GST_SECOND;


  difference = ABS (priv->duration - new_duration);
  if (difference > 1e-3)
    {
      CLUTTER_GST_NOTE (MEDIA, "duration: %.02f", new_duration);
      priv->duration = new_duration;

      if (difference > 1.0)
        g_object_notify (G_OBJECT (player), "duration");
    }
}
