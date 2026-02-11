clutter_box_layout_get_property (GObject    *gobject,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  ClutterBoxLayoutPrivate *priv = CLUTTER_BOX_LAYOUT (gobject)->priv;

  switch (prop_id)
    {
    case PROP_VERTICAL:
      g_value_set_boolean (value,
                           priv->orientation == CLUTTER_ORIENTATION_VERTICAL);
      break;

    case PROP_ORIENTATION:
      g_value_set_enum (value, priv->orientation);
      break;

    case PROP_HOMOGENEOUS:
      g_value_set_boolean (value, priv->is_homogeneous);
      break;

    case PROP_SPACING:
      g_value_set_uint (value, priv->spacing);
      break;

    case PROP_PACK_START:
      g_value_set_boolean (value, priv->is_pack_start);
      break;

    case PROP_USE_ANIMATIONS:
      g_value_set_boolean (value, priv->use_animations);
      break;

    case PROP_EASING_MODE:
      g_value_set_ulong (value, priv->easing_mode);
      break;

    case PROP_EASING_DURATION:
      g_value_set_uint (value, priv->easing_duration);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
      break;
    }
}
