netsnmp_create_table_data(const char *name)
{
    netsnmp_table_data *table = SNMP_MALLOC_TYPEDEF(netsnmp_table_data);
    if (name && table)
        table->name = strdup(name);
    return table;
}
