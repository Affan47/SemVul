goa_realm_object_manager_client_get_proxy_type (GDBusObjectManagerClient *manager G_GNUC_UNUSED, const gchar *object_path G_GNUC_UNUSED, const gchar *interface_name, gpointer user_data G_GNUC_UNUSED)
{
  static gsize once_init_value = 0;
  static GHashTable *lookup_hash;
  GType ret;

  if (interface_name == NULL)
    return GOA_REALM_TYPE_OBJECT_PROXY;
  if (g_once_init_enter (&once_init_value))
    {
      lookup_hash = g_hash_table_new (g_str_hash, g_str_equal);
      g_hash_table_insert (lookup_hash, (gpointer) "org.freedesktop.realmd.Provider", GSIZE_TO_POINTER (GOA_REALM_TYPE_PROVIDER_PROXY));
      g_hash_table_insert (lookup_hash, (gpointer) "org.freedesktop.realmd.Service", GSIZE_TO_POINTER (GOA_REALM_TYPE_SERVICE_PROXY));
      g_hash_table_insert (lookup_hash, (gpointer) "org.freedesktop.realmd.Realm", GSIZE_TO_POINTER (GOA_REALM_TYPE_COMMON_PROXY));
      g_hash_table_insert (lookup_hash, (gpointer) "org.freedesktop.realmd.Kerberos", GSIZE_TO_POINTER (GOA_REALM_TYPE_KERBEROS_PROXY));
      g_hash_table_insert (lookup_hash, (gpointer) "org.freedesktop.realmd.KerberosMembership", GSIZE_TO_POINTER (GOA_REALM_TYPE_KERBEROS_MEMBERSHIP_PROXY));
      g_once_init_leave (&once_init_value, 1);
    }
  ret = (GType) GPOINTER_TO_SIZE (g_hash_table_lookup (lookup_hash, interface_name));
  if (ret == (GType) 0)
    ret = G_TYPE_DBUS_PROXY;
  return ret;
}
