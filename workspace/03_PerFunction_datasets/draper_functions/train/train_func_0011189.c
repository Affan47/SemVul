cpl_table_unselect_all(cpl_table *table)
{

    if (table == 0x0)
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);

    if (table->select)
        cpl_free(table->select);
    table->select = NULL;
    table->selectcount = 0;

    return CPL_ERROR_NONE;

}
