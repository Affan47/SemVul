get_property (GObject *object,
              guint property_id,
              GValue *value,
              GParamSpec *spec)
{
  TpTestsSimpleConnection *self = TP_TESTS_SIMPLE_CONNECTION (object);

  switch (property_id) {
    case PROP_ACCOUNT:
      g_value_set_string (value, self->priv->account);
      break;
    case PROP_BREAK_PROPS:
      g_value_set_boolean (value, self->priv->break_fastpath_props);
      break;
    case PROP_DBUS_STATUS:
      if (self->priv->break_fastpath_props)
        {
          g_debug ("returning broken value for Connection.Status");
          g_value_set_uint (value, 0xdeadbeefU);
        }
      else
        {
          g_value_set_uint (value,
              tp_base_connection_get_status (TP_BASE_CONNECTION (self)));
        }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, spec);
  }
}
