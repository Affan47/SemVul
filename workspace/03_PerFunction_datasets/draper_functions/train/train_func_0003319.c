ges_track_audio_transition_duration_changed (GESTrackObject * object,
    guint64 duration)
{
  GESTrackAudioTransition *self;
  GstElement *gnlobj = ges_track_object_get_gnlobject (object);

  GValue zero = { 0, };
  GValue one = { 0, };

  self = GES_TRACK_AUDIO_TRANSITION (object);

  GST_LOG ("updating controller: gnlobj (%p) acontroller(%p) bcontroller(%p)",
      gnlobj, self->priv->a_controller, self->priv->b_controller);

  if (G_UNLIKELY ((!gnlobj || !self->priv->a_control_source ||
              !self->priv->b_control_source)))
    return;

  GST_INFO ("duration: %" G_GUINT64_FORMAT, duration);
  g_value_init (&zero, G_TYPE_DOUBLE);
  g_value_init (&one, G_TYPE_DOUBLE);
  g_value_set_double (&zero, 0.0);
  g_value_set_double (&one, 1.0);

  GST_LOG ("setting values on controller");

  gst_interpolation_control_source_unset_all (self->priv->a_control_source);
  gst_interpolation_control_source_set (self->priv->a_control_source, 0, &one);
  gst_interpolation_control_source_set (self->priv->a_control_source,
      duration, &zero);

  gst_interpolation_control_source_unset_all (self->priv->b_control_source);
  gst_interpolation_control_source_set (self->priv->b_control_source, 0, &zero);
  gst_interpolation_control_source_set (self->priv->b_control_source, duration,
      &one);

  GST_LOG ("done updating controller");
}
