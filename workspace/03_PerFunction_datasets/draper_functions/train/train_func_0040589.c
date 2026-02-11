tpl_entity_set_property (GObject *object,
    guint param_id,
    const GValue *value,
    GParamSpec *pspec)
{
  TplEntityPriv *priv = TPL_ENTITY (object)->priv;

  switch (param_id)
    {
      case PROP_TYPE:
        priv->type = g_value_get_int (value);
        break;
      case PROP_IDENTIFIER:
        g_assert (priv->identifier == NULL);
        priv->identifier = g_value_dup_string (value);
        break;
      case PROP_ALIAS:
        g_assert (priv->alias == NULL);
        priv->alias = g_value_dup_string (value);
        break;
      case PROP_AVATAR_TOKEN:
        g_assert (priv->avatar_token == NULL);
        priv->avatar_token = g_value_dup_string (value);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
        break;
  };

}
