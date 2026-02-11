mx_actor_manager_get_property (GObject    *object,
                               guint       property_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  MxActorManagerPrivate *priv = MX_ACTOR_MANAGER (object)->priv;

  switch (property_id)
    {
    case PROP_STAGE:
      g_value_set_object (value, priv->stage);
      break;

    case PROP_TIME_SLICE:
      g_value_set_uint (value, priv->time_slice);
      break;

    case PROP_N_OPERATIONS:
      g_value_set_uint (value, g_queue_get_length (priv->ops));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
