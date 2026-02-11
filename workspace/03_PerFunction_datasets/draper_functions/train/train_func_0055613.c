tp_proxy_signal_connection_v0_new (TpProxy *self,
                                   GQuark iface,
                                   const gchar *member,
                                   const GType *expected_types,
                                   GCallback collect_args,
                                   TpProxyInvokeFunc invoke_callback,
                                   GCallback callback,
                                   gpointer user_data,
                                   GDestroyNotify destroy,
                                   GObject *weak_object,
                                   GError **error)
{
  TpProxySignalConnection *sc;
  DBusGProxy *iface_proxy = tp_proxy_get_interface_by_id (self,
      iface, error);

  if (iface_proxy == NULL)
    {
      if (destroy != NULL)
        destroy (user_data);

      return NULL;
    }

  if (expected_types[0] == G_TYPE_INVALID)
    {
      collect_args = G_CALLBACK (collect_none);
    }
  else
    {
      g_return_val_if_fail (collect_args != NULL, NULL);
    }

  sc = g_slice_new0 (TpProxySignalConnection);

  MORE_DEBUG ("(proxy=%p, if=%s, sig=%s, collect=%p, invoke=%p, "
      "cb=%p, ud=%p, dn=%p, wo=%p) -> %p",
      self, g_quark_to_string (iface), member, collect_args,
      invoke_callback, callback, user_data, destroy, weak_object, sc);

  sc->refcount = 1;
  sc->proxy = self;
  sc->iface_proxy = g_object_ref (iface_proxy);
  sc->member = g_strdup (member);
  sc->collect_args = collect_args;
  sc->invoke_callback = invoke_callback;
  sc->callback = callback;
  sc->user_data = user_data;
  sc->destroy = destroy;
  sc->weak_object = weak_object;

  if (weak_object != NULL)
    g_object_weak_ref (weak_object, tp_proxy_signal_connection_lost_weak_ref,
        sc);

  g_signal_connect (self, "invalidated",
      G_CALLBACK (tp_proxy_signal_connection_proxy_invalidated), sc);

  g_signal_connect (iface_proxy, "destroy",
      G_CALLBACK (_tp_proxy_signal_connection_dgproxy_destroy), sc);

  dbus_g_proxy_connect_signal (iface_proxy, member, collect_args, sc,
      tp_proxy_signal_connection_dropped);

  return sc;
}
