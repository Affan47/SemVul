_tp_channel_get_properties (TpChannel *self)
{

  if (self->priv->handle_type != TP_UNKNOWN_HANDLE_TYPE
      && (self->priv->handle != 0 ||
          self->priv->handle_type == TP_HANDLE_TYPE_NONE)
      && self->priv->channel_type != 0


      && tp_asv_get_string (self->priv->channel_properties,
        TP_PROP_CHANNEL_TARGET_ID) != NULL
      && tp_asv_get_string (self->priv->channel_properties,
        TP_PROP_CHANNEL_INITIATOR_ID) != NULL
      )
    {
      gboolean valid;

      tp_asv_get_uint32 (self->priv->channel_properties,
          TP_PROP_CHANNEL_INITIATOR_HANDLE, &valid);

      if (!valid)
        goto missing;

      tp_asv_get_boolean (self->priv->channel_properties,
          TP_PROP_CHANNEL_REQUESTED, &valid);

      if (!valid)
        goto missing;

      _tp_channel_continue_introspection (self);
      return;
    }

missing:
  tp_cli_dbus_properties_call_get_all (self, -1,
      TP_IFACE_CHANNEL, _tp_channel_got_properties, NULL, NULL, NULL);
}
