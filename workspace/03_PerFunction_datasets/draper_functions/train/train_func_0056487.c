cpl_table_shift_column(cpl_table *table, const char *name,
                                      cpl_size shift)
{


    cpl_column *column = cpl_table_find_column_(table, name);

    return !column || cpl_column_shift(column, shift) ||
        cpl_table_select_all(table)
        ? cpl_error_set_where_() : CPL_ERROR_NONE;
}
