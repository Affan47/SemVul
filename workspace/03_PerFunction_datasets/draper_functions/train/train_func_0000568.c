cpl_table_get_column_names(const cpl_table *table)
{
    cpl_array  *names;
    cpl_size    i;


    if (table == NULL) {
        cpl_error_set_(CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    names = cpl_array_new(table->nc, CPL_TYPE_STRING);
    for (i = 0; i < table->nc; i++)
       cpl_array_set_string(names, i, cpl_column_get_name(table->columns[i]));

    return names;

}
