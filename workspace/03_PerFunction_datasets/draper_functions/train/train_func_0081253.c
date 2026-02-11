gwy_inventory_nth_item_updated(GwyInventory *inventory,
                               guint n)
{
    g_return_if_fail(GWY_IS_INVENTORY(inventory));
    g_return_if_fail(n < inventory->items->len);

    g_signal_emit(inventory, gwy_inventory_signals[ITEM_UPDATED], 0, n);
}
