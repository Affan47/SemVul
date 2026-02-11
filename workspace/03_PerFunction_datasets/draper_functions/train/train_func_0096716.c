ges_title_clip_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GESTitleClipPrivate *priv = GES_TITLE_CLIP (object)->priv;

  switch (property_id) {
    case PROP_TEXT:
      g_value_set_string (value, priv->text);
      break;
    case PROP_FONT_DESC:
      g_value_set_string (value, priv->font_desc);
      break;
    case PROP_HALIGNMENT:
      g_value_set_enum (value, priv->halign);
      break;
    case PROP_VALIGNMENT:
      g_value_set_enum (value, priv->valign);
      break;
    case PROP_COLOR:
      g_value_set_uint (value, priv->color);
      break;
    case PROP_BACKGROUND:
      g_value_set_uint (value, priv->background);
      break;
    case PROP_XPOS:
      g_value_set_double (value, priv->xpos);
      break;
    case PROP_YPOS:
      g_value_set_double (value, priv->ypos);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}
