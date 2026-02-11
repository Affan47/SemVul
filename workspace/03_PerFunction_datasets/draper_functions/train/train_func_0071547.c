netsnmp_table_data_delete_row(netsnmp_table_row *row)
{
    void           *data;

    if (!row)
        return NULL;


    if (row->indexes)
        snmp_free_varbind(row->indexes);
    SNMP_FREE(row->index_oid);
    data = row->data;
    free(row);


    return data;
}
