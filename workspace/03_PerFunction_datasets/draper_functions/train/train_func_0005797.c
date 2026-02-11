netsnmp_delete_table_data_set(netsnmp_table_data_set *table_set)
{
    netsnmp_table_data_set_storage *ptr, *next;
    netsnmp_table_row *prow, *pnextrow;

    for (ptr = table_set->default_row; ptr; ptr = next) {
        next = ptr->next;
        free(ptr);
    }
    table_set->default_row = NULL;
    for (prow = table_set->table->first_row; prow; prow = pnextrow) {
        pnextrow = prow->next;
        netsnmp_table_dataset_remove_and_delete_row(table_set, prow);
    }
    table_set->table->first_row = NULL;
    netsnmp_table_data_delete_table(table_set->table);
    free(table_set);
}
