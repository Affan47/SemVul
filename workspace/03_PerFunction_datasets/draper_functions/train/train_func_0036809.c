unity_webapps_interest_tracker_get_property (GObject *object, guint property_id,
					   GValue *value, GParamSpec *pspec)
{
  UnityWebappsInterestTracker *self;

  self = UNITY_WEBAPPS_INTEREST_TRACKER (object);

  switch (property_id)
    {
    case PROP_MOST_RECENT_INTEREST:
      g_value_set_int (value, self->priv->most_recent_interest);
      break;
    case PROP_WINDOW_TRACKER:
      g_value_set_object (value, self->priv->window_tracker);
      break;
    case PROP_INTEREST_MANAGER:
      g_value_set_object (value, self->priv->interest_manager);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}
