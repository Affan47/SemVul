cpl_table_not_selected(cpl_table *table)
{

    cpl_size    length;


    if (table == 0x0) {
        cpl_error_set_(CPL_ERROR_NULL_INPUT);
        return -1;
    }

    if (table->selectcount == 0)
        return table->selectcount = table->nr;

    if (table->selectcount == table->nr)
        return table->selectcount = 0;

    length = table->nr;

    while (length--) {
        if (table->select[length])
            table->select[length] = 0;
        else
            table->select[length] = 1;
    }

    return table->selectcount = table->nr - table->selectcount;

}
