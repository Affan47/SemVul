tpaw_account_settings_set_property (GObject *object,
    guint prop_id,
    const GValue *value,
    GParamSpec *pspec)
{
  TpawAccountSettings *self = TPAW_ACCOUNT_SETTINGS (object);

  switch (prop_id)
    {
      case PROP_ACCOUNT:
        self->priv->account = g_value_dup_object (value);
        break;
      case PROP_CM_NAME:
        self->priv->cm_name = g_value_dup_string (value);
        break;
      case PROP_PROTOCOL:
        self->priv->protocol = g_value_dup_string (value);
        break;
      case PROP_SERVICE:
        self->priv->service = g_value_dup_string (value);
        break;
      case PROP_DISPLAY_NAME:
        self->priv->display_name = g_value_dup_string (value);
        break;
      case PROP_DISPLAY_NAME_OVERRIDDEN:
        self->priv->display_name_overridden = g_value_get_boolean (value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
