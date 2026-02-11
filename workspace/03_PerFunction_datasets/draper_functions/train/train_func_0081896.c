tp_proxy_add_interface_by_id (TpProxy *self,
                              GQuark iface)
{
  DBusGProxy *iface_proxy = g_datalist_id_get_data (&self->priv->interfaces,
      iface);

  g_return_val_if_fail
      (tp_dbus_check_valid_interface_name (g_quark_to_string (iface),
          NULL),
       NULL);

  g_return_val_if_fail (tp_proxy_get_invalidated (self) == NULL, NULL);

  if (iface_proxy == NULL)
    {


      g_datalist_id_set_data_full (&self->priv->interfaces, iface,
          self, NULL);
    }

  return iface_proxy;
}
