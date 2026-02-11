gdm_display_store_lookup (GdmDisplayStore *store,
                          const char      *id)
{
        StoredDisplay *stored_display;

        g_return_val_if_fail (store != NULL, NULL);
        g_return_val_if_fail (id != NULL, NULL);

        stored_display = g_hash_table_lookup (store->priv->displays,
                                              id);
        if (stored_display == NULL) {
                return NULL;
        }

        return stored_display->display;
}
