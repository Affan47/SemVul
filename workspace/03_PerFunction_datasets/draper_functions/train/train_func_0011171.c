cpl_table_wrap_float_complex(cpl_table *table,
                                            float complex *data,
                                            const char *name)
{

    cpl_column *column;


    if (table == 0x0 || data == 0x0 || name == 0x0)
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);

    if (cpl_table_find_column(table, name))
        return cpl_error_set_(CPL_ERROR_ILLEGAL_OUTPUT);

    column = cpl_column_wrap_float_complex(data, table->nr);
    cpl_column_set_name(column, name);
    cpl_table_append_column(table, column);

    return CPL_ERROR_NONE;

}
