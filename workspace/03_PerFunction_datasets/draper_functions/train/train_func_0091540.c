tp_account_channel_request_get_property (GObject *object,
    guint property_id,
    GValue *value,
    GParamSpec *pspec)
{
  TpAccountChannelRequest *self = TP_ACCOUNT_CHANNEL_REQUEST (
      object);

  switch (property_id)
    {
      case PROP_ACCOUNT:
        g_value_set_object (value, self->priv->account);
        break;

      case PROP_REQUEST:
        g_value_set_boxed (value, self->priv->request);
        break;

      case PROP_REQUEST_VARDICT:
        g_value_take_variant (value,
            tp_account_channel_request_dup_request (self));
        break;

      case PROP_USER_ACTION_TIME:
        g_value_set_int64 (value, self->priv->user_action_time);
        break;

      case PROP_CHANNEL_REQUEST:
        g_value_set_object (value, self->priv->chan_request);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
  }
}
