bs_callback_table_remove(BSCallbackTable *table, gint id)
{
    if (bs_callback_list_contains_callback(table->list, id)) {
        bs_callback_list_remove(table->list, id);
        return;
    }

    g_hash_table_foreach(table->table, remove_cb_from_value, &id);
}
