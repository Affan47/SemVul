gncOrderRemoveEntry (GncOrder *order, GncEntry *entry)
{
    if (!order || !entry) return;

    gncOrderBeginEdit (order);
    gncEntrySetOrder (entry, NULL);
    order->entries = g_list_remove (order->entries, entry);
    mark_order (order);
    gncOrderCommitEdit (order);
}
