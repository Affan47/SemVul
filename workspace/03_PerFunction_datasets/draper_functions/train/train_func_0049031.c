tp_proxy_get_property (GObject *object,
                       guint property_id,
                       GValue *value,
                       GParamSpec *pspec)
{
  TpProxy *self = TP_PROXY (object);

  switch (property_id)
    {
    case PROP_DBUS_DAEMON:
      if (TP_IS_DBUS_DAEMON (self))
        {
          g_value_set_object (value, self);
        }
      else
        {
          g_value_set_object (value, self->dbus_daemon);
        }
      break;
    case PROP_DBUS_CONNECTION:
      g_value_set_boxed (value, self->dbus_connection);
      break;
    case PROP_BUS_NAME:
      g_value_set_string (value, self->bus_name);
      break;
    case PROP_OBJECT_PATH:
      g_value_set_string (value, self->object_path);
      break;
    case PROP_INTERFACES:
        {
          GPtrArray *strings = g_ptr_array_new ();

          g_datalist_foreach (&self->priv->interfaces,
              dup_quark_into_ptr_array, strings);
          g_ptr_array_add (strings, NULL);
          g_value_take_boxed (value, g_ptr_array_free (strings, FALSE));
        }
      break;
    case PROP_FACTORY:
      g_value_set_object (value, self->priv->factory);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}
