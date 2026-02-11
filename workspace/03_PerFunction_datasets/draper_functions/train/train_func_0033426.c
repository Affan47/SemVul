tpl_log_iter_xml_get_property (GObject *object,
    guint param_id,
    GValue *value,
    GParamSpec *pspec)
{
  TplLogIterXmlPriv *priv;

  priv = TPL_LOG_ITER_XML (object)->priv;

  switch (param_id)
    {
    case PROP_ACCOUNT:
      g_value_set_object (value, priv->account);
      break;

    case PROP_STORE:
      g_value_set_object (value, priv->store);
      break;

    case PROP_TARGET:
      g_value_set_object (value, priv->target);
      break;

    case PROP_TYPE_MASK:
      g_value_set_int (value, priv->type_mask);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}
