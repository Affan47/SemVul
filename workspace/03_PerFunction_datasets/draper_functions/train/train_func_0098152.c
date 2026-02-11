cryptui_keyset_get_closure (CryptUIKeyset *keyset, const gchar *key)
{
    gpointer closure = g_hash_table_lookup (keyset->priv->keys, key);
    g_return_val_if_fail (closure != NULL, NULL);


    if (closure == GINT_TO_POINTER (TRUE))
        return NULL;

    return closure;
}
