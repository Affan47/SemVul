cpl_table_unselect_row(cpl_table *table, cpl_size row)
{

    int          length;


    if (table == 0x0)
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);

    if (row < 0 || row >= table->nr)
        return cpl_error_set_(CPL_ERROR_ACCESS_OUT_OF_RANGE);

    if (table->selectcount == 0)
        return CPL_ERROR_NONE;

    length = table->nr;

    if (table->selectcount == length)
        table->select = cpl_malloc(table->nr * sizeof(cpl_column_flag));

    if (table->selectcount == length)
        while (length--)
            table->select[length] = 1;

    if (table->select[row] == 1) {
        table->select[row] = 0;
        table->selectcount--;

        if (table->selectcount == 0) {
            if (table->select)
                cpl_free(table->select);
            table->select = NULL;
        }
    }

    return CPL_ERROR_NONE;

}
