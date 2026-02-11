gwy_inventory_set_default_item_name(GwyInventory *inventory,
                                    const gchar *name)
{
    gboolean emit_change = FALSE;

    g_return_if_fail(GWY_IS_INVENTORY(inventory));
    if (!name) {
        emit_change = inventory->has_default;
        inventory->has_default = FALSE;
    }
    else {
        if (!inventory->has_default) {
            emit_change = TRUE;
            inventory->has_default = TRUE;
        }

        if (!inventory->default_key) {
            inventory->default_key = g_string_new(name);
            emit_change = TRUE;
        }
        else {
            if (!gwy_strequal(inventory->default_key->str, name))
                emit_change = TRUE;
            g_string_assign(inventory->default_key, name);
        }
    }

    if (emit_change)
        g_signal_emit(inventory, gwy_inventory_signals[DEFAULT_CHANGED], 0);
}
