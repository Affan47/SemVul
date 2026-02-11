clutter_behaviour_opacity_set_property (GObject      *gobject,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
  ClutterBehaviourOpacity *self = CLUTTER_BEHAVIOUR_OPACITY (gobject);

  switch (prop_id)
    {
    case PROP_OPACITY_START:
      clutter_behaviour_opacity_set_bounds (self,
                                            g_value_get_uint (value),
                                            self->priv->opacity_end);
      break;

    case PROP_OPACITY_END:
      clutter_behaviour_opacity_set_bounds (self,
                                            self->priv->opacity_start,
                                            g_value_get_uint (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
      break;
    }
}
