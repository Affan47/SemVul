sw_service_iface_get_dynamic_capabilities (SwServiceIface *self,
    DBusGMethodInvocation *context)
{
  sw_service_iface_get_dynamic_capabilities_impl impl = (SW_SERVICE_IFACE_GET_CLASS (self)->get_dynamic_capabilities);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR,
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}
