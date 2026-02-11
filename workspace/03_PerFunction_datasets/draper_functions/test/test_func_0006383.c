equal_func_lookup (GType type1, GType type2)
{
    EqualEntry entry;

    entry.type1 = type1;
    do {
        entry.type2 = type2;
        do {
            EqualEntry *found_entry;

            found_entry = g_bsearch_array_lookup(equal_entries,
                                                 &equal_bconfig,
                                                 &entry);
            if (found_entry) {
                if (g_type_value_table_peek(entry.type1) ==
                    g_type_value_table_peek(type1) &&
                    g_type_value_table_peek(entry.type2) ==
                    g_type_value_table_peek(type2))
                    return found_entry->func;
            }

            entry.type2 = g_type_parent(entry.type2);
        } while (entry.type2);

        entry.type1 = g_type_parent(entry.type1);
    } while (entry.type1);

    return NULL;
}
