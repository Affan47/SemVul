unity_webapps_gen_context_proxy_get_property (GObject      *object,
  guint         prop_id,
  GValue       *value,
  GParamSpec   *pspec G_GNUC_UNUSED)
{
  const _ExtendedGDBusPropertyInfo *info;
  GVariant *variant;
  g_assert (prop_id != 0 && prop_id - 1 < 5);
  info = _unity_webapps_gen_context_property_info_pointers[prop_id - 1];
  variant = g_dbus_proxy_get_cached_property (G_DBUS_PROXY (object), info->parent_struct.name);
  if (info->use_gvariant)
    {
      g_value_set_variant (value, variant);
    }
  else
    {
      if (variant != NULL)
        g_dbus_gvariant_to_gvalue (variant, value);
    }
  if (variant != NULL)
    g_variant_unref (variant);
}
