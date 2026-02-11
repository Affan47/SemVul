cph_iface_mechanism_call_printer_add_sync (
    CphIfaceMechanism *proxy,
    const gchar *arg_name,
    const gchar *arg_uri,
    const gchar *arg_ppd,
    const gchar *arg_info,
    const gchar *arg_location,
    gchar **out_error,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "PrinterAdd",
    g_variant_new ("(sssss)",
                   arg_name,
                   arg_uri,
                   arg_ppd,
                   arg_info,
                   arg_location),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(s)",
                 out_error);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}
