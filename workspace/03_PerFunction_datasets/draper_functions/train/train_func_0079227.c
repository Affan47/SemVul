cpl_table_extract_column(cpl_table *table, const char *name)
{

    cpl_column  *column  = cpl_table_find_column(table, name);


    if (column) {

        const cpl_size width   = cpl_table_get_ncol(table);
        cpl_size       i, j;

        for (i = 0; i < width; i++)
            if (column == table->columns[i])
                break;

        j = i + 1;
        while(j < width)
            table->columns[i++] = table->columns[j++];

        table->nc--;
        if (table->nc) {
            table->columns = cpl_realloc(table->columns,
                             table->nc * sizeof(column));
        }
        else {
            cpl_free(table->columns);
            table->columns = NULL;
        }

        if (table->nc == 0)
            cpl_table_select_all(table);

    }

    return column;

}
