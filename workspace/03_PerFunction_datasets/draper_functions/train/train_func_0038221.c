TXT_PageTable(TXT_UNCAST_ARG(table), int pagex, int pagey)
{
    TXT_CAST_ARG(txt_table_t, table);
    unsigned int *column_widths;
    unsigned int *row_heights;
    int rows;
    int changed = 0;

    rows = TableRows(table);

    row_heights = malloc(sizeof(int) * rows);
    column_widths = malloc(sizeof(int) * table->columns);

    CalcRowColSizes(table, row_heights, column_widths);

    if (pagex)
    {

    }

    if (pagey)
    {
        int new_x, new_y;
        int distance = 0;
        int dir;


        if (pagey > 0)
        {
            dir = 1;
        }
        else
        {
            dir = -1;
        }


        new_y = table->selected_y;

        while (new_y >= 0 && new_y < rows)
        {


            distance += row_heights[new_y];


            new_y += dir;

            new_x = FindSelectableColumn(table, new_y, table->selected_x);

            if (new_x >= 0)
            {


                ChangeSelection(table, new_x, new_y);
                changed = 1;


                if (distance >= abs(pagey))
                {
                    break;
                }
            }
        }
    }

    free(row_heights);
    free(column_widths);

    return changed;
}
