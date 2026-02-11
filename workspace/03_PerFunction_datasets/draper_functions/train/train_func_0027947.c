gsm_store_add (GsmStore   *store,
               const char *id,
               GObject    *object)
{
        g_return_val_if_fail (store != NULL, FALSE);
        g_return_val_if_fail (id != NULL, FALSE);
        g_return_val_if_fail (object != NULL, FALSE);


        if (store->priv->locked) {
                return FALSE;
        }

        g_debug ("GsmStore: Adding object id %s to store", id);

        g_hash_table_insert (store->priv->objects,
                             g_strdup (id),
                             g_object_ref (object));

        g_signal_emit (store, signals [ADDED], 0, id);

        return TRUE;
}
