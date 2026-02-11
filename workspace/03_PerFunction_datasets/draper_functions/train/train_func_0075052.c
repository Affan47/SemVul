_mteTrigger_countEntries(void)
{
    struct mteTrigger *entry;
    netsnmp_tdata_row *row;
    long count = 0;

    for (row = netsnmp_tdata_row_first(trigger_table_data);
         row;
         row = netsnmp_tdata_row_next(trigger_table_data, row)) {
        entry  = (struct mteTrigger *)row->data;
        count += entry->count;
    }

    return count;
}
