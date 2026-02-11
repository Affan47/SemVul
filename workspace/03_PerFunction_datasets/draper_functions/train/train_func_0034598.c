netsnmp_table_dataset_add_index(netsnmp_table_data_set *table, u_char type)
{
    if (!table)
        return;
    netsnmp_table_data_add_index(table->table, type);
}
