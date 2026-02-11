facebook_contact_view_get_property (GObject    *self,
                                 guint       property_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  SwFacebookContactViewPrivate *priv = GET_PRIVATE (self);

  switch (property_id)
    {
      case PROP_PROXY:
        g_value_set_object (value, priv->proxy);
        break;

      case PROP_QUERY:
        g_value_set_string (value, priv->query);
        break;

      case PROP_PARAMS:
        g_value_set_boxed (value, priv->params);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (self, property_id, pspec);
        break;
    }
}
