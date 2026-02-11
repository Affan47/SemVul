cpl_table_erase_invalid(cpl_table *table)
{

    cpl_size    length     = 0;
    cpl_size    width      = 0;
    cpl_size    new_width;
    cpl_size    count      = 0;
    int         any_null;


    if (table == 0x0)
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);

    length = cpl_table_get_nrow(table);
    width  = cpl_table_get_ncol(table);

    while (width--)
        if (!cpl_column_has_valid(table->columns[width]))
            cpl_table_erase_column(table,
                             cpl_column_get_name(table->columns[width]));

    new_width = cpl_table_get_ncol(table);

    if (new_width == 0)
        return CPL_ERROR_NONE;

    while (length--) {

        width = new_width;

        any_null = 0;
        while (width--) {
            if (cpl_column_is_invalid(table->columns[width], length)) {
                any_null = 1;
                break;
            }
        }

        if (any_null) {
            count++;
        }
        else {
            if (count) {
                cpl_table_erase_window(table, length + 1, count);
                count = 0;
            }
        }

    }

    if (count)
        cpl_table_erase_window(table, 0, count);

    return cpl_table_select_all(table);

}
