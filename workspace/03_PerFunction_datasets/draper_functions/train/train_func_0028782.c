clutter_behaviour_get_property (GObject    *object,
			        guint       prop_id,
			        GValue     *value,
			        GParamSpec *pspec)
{
  ClutterBehaviour        *behaviour = CLUTTER_BEHAVIOUR (object);
  ClutterBehaviourPrivate *priv = behaviour->priv;

  switch (prop_id)
    {
    case PROP_ALPHA:
      g_value_set_object (value, priv->alpha);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
