_secret_gen_collection_call_create_item_sync (
    SecretGenCollection *proxy,
    GVariant *arg_properties,
    GVariant *arg_secret,
    gboolean arg_replace,
    gchar **out_item,
    gchar **out_prompt,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "CreateItem",
    g_variant_new ("(@a{sv}@(oayays)b)",
                   arg_properties,
                   arg_secret,
                   arg_replace),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(oo)",
                 out_item,
                 out_prompt);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}
