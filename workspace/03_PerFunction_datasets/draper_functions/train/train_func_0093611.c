gwy_inventory_item_updated(GwyInventory *inventory,
                           const gchar *name)
{
    guint i;

    g_return_if_fail(GWY_IS_INVENTORY(inventory));
    if (!(i = gwy_inventory_lookup(inventory, name)))
        g_warning("Item `%s' does not exist", name);
    else
        gwy_inventory_item_updated_real(inventory, i-1);
}
