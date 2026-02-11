ibus_lookup_table_is_round (IBusLookupTable *table)
{
    g_assert (IBUS_IS_LOOKUP_TABLE (table));

    return table->round;
}
