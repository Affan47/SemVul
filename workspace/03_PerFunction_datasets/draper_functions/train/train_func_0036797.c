g_vfs_keyring_save_password (const gchar  *username,
                             const gchar  *host,
                             const gchar  *domain,
                             const gchar  *protocol,
			     const gchar  *object,
			     const gchar  *authtype,
			     guint32       port,
                             const gchar  *password,
                             GPasswordSave flags)
{
#ifdef HAVE_KEYRING
  const gchar       *keyring;
  GHashTable        *attributes;
  gchar             *label;
  gboolean           ret;

  if (flags == G_PASSWORD_SAVE_NEVER)
    return FALSE;

  keyring = (flags == G_PASSWORD_SAVE_FOR_SESSION) ? SECRET_COLLECTION_SESSION : SECRET_COLLECTION_DEFAULT;

  label = build_network_label (username, host, object, port);
  attributes = build_network_attributes (username, host, domain, protocol, object, authtype, port);

  ret = secret_password_storev_sync (SECRET_SCHEMA_COMPAT_NETWORK, attributes,
                                     keyring, label, password, NULL, NULL);

  g_free (label);
  g_hash_table_unref (attributes);

  return ret;
#else
  return FALSE;
#endif
}
