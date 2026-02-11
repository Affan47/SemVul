do_get_property (GObject *object,
    guint prop_id,
    GValue *value,
    GParamSpec *pspec)
{
  TpawAccountWidget *self = TPAW_ACCOUNT_WIDGET (object);

  switch (prop_id)
    {
    case PROP_PROTOCOL:
      g_value_set_string (value,
        tpaw_account_settings_get_protocol (self->priv->settings));
      break;
    case PROP_SETTINGS:
      g_value_set_object (value, self->priv->settings);
      break;
    case PROP_SIMPLE:
      g_value_set_boolean (value, self->priv->simple);
      break;
    case PROP_CREATING_ACCOUNT:
      g_value_set_boolean (value, self->priv->creating_account);
      break;
    case PROP_OTHER_ACCOUNTS_EXIST:
      g_value_set_boolean (value, self->priv->other_accounts_exist);
      break;
    case PROP_ACTION_AREA:
      g_value_set_object (value, self->priv->action_area);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}
