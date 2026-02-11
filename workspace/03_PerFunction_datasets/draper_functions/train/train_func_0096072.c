sp_unit_get_list(guint bases)
{
    g_return_val_if_fail((bases & ~SP_UNITS_ALL) == 0, NULL);

    GSList *units = NULL;
    for (unsigned i = sp_num_units ; i--; ) {
        if (bases & sp_units[i].base) {
            units = g_slist_prepend(units, (gpointer) &sp_units[i]);
        }
    }

    return units;
}
