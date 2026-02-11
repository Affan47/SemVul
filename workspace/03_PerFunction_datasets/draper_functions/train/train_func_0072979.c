gncTaxTableRemoveEntry (GncTaxTable *table, GncTaxTableEntry *entry)
{
    if (!table || !entry) return;
    gncTaxTableBeginEdit (table);
    entry->table = NULL;
    table->entries = g_list_remove (table->entries, entry);
    mark_table (table);
    mod_table (table);
    gncTaxTableCommitEdit (table);
}
