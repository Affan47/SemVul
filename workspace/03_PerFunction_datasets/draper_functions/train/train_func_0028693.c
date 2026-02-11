qif_object_list_count(QifContext ctx, const char *type)
{
    GList *list;

    g_return_val_if_fail(ctx, 0);
    g_return_val_if_fail(ctx->object_lists, 0);
    g_return_val_if_fail(type, 0);

    list = g_hash_table_lookup(ctx->object_lists, type);
    return g_list_length(list);
}
