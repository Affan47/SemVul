mx_deform_texture_get_property (GObject    *object,
                                guint       property_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  MxDeformTexturePrivate *priv = MX_DEFORM_TEXTURE (object)->priv;

  switch (property_id)
    {
    case PROP_TILES_X:
      g_value_set_int (value, priv->tiles_x);
      break;

    case PROP_TILES_Y:
      g_value_set_int (value, priv->tiles_y);
      break;

    case PROP_FRONT:
      g_value_set_object (value, priv->front);
      break;

    case PROP_BACK:
      g_value_set_object (value, priv->back);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
