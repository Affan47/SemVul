calculate_first_column(ali_prealigner_column * akt_column)
{
    unsigned long   pos_y;

    calculate_first_column_first_cell(&(*akt_column->cells)[0]);

    for (pos_y = 1; pos_y < akt_column->column_length; pos_y++)
        calculate_first_column_cell(&(*akt_column->cells)[pos_y - 1],
                                    &(*akt_column->cells)[pos_y],
                                    pos_y);
}
