qif_object_map_lookup(QifContext ctx, const char *type, const char *key)
{
    GHashTable *ht;

    g_return_val_if_fail(ctx, NULL);
    g_return_val_if_fail(ctx->object_maps, NULL);
    g_return_val_if_fail(type, NULL);
    g_return_val_if_fail(key, NULL);

    ht = g_hash_table_lookup(ctx->object_maps, type);
    if (!ht) return NULL;

    return g_hash_table_lookup(ht, key);
}
