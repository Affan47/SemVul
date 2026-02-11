cpl_column_add_to_float_complex(cpl_column *column,
                                            double complex value)
{

    cpl_size       nullcount = cpl_column_count_invalid(column);
    cpl_size       length    = cpl_column_get_size(column);
    float complex *fp        = cpl_column_get_data_float_complex(column);
    int           *np        = cpl_column_get_data_invalid(column);
    cpl_size       i;


    if (value == 0.0)
        return;

    if (nullcount == length)
        return;

    if (nullcount == 0)
        for (i = 0; i < length; i++)
            *fp++ += value;
    else
        for (i = 0; i < length; i++, fp++, np++)
            if (*np == 0)
                *fp += value;

}
