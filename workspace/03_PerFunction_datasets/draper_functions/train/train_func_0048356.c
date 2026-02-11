key_removed (DBusGProxy *proxy, const char *key, CryptUIKeyset *keyset)
{
    gchar *k = NULL;

    if (!keyset->priv->expand_keys)
        key = k = cryptui_key_get_base (key);

    if (g_hash_table_lookup (keyset->priv->keys, key)) {


        g_hash_table_remove (keyset->priv->key_props, key);

        remove_key (key, NULL, keyset);
    }

    g_free (k);
}
