hybrid_info_item_create(const gchar *name, const gchar *value)
{
    HybridInfoItem *item;

    g_return_val_if_fail(name != NULL, NULL);

    item = g_new0(HybridInfoItem, 1);
    item->name = g_strdup(name);
    item->value = g_strdup(value);

    return item;
}
