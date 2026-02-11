cpl_column_fill_invalid_double_complex(cpl_column *column,
                                                      double complex code)
{

    const char     *fid    = "cpl_column_fill_invalid_double_complex";
    cpl_type        type   = cpl_column_get_type(column);
    cpl_size        length = cpl_column_get_size(column);
    int            *np;
    double complex *dp;
    cpl_size        i;
    cpl_column     *acolumn;
    cpl_array     **array;


    if (column == 0x0)
        return cpl_error_set(fid, CPL_ERROR_NULL_INPUT);

    if (!(type & CPL_TYPE_DOUBLE_COMPLEX))
        return cpl_error_set(fid, CPL_ERROR_TYPE_MISMATCH);

    if (type & CPL_TYPE_POINTER) {

        array = cpl_column_get_data_array(column);

        while (length--) {
            if (array[length]) {
                acolumn = cpl_array_get_column(array[length]);
                cpl_column_fill_invalid_double_complex(acolumn, code);
            }
        }
        return CPL_ERROR_NONE;
    }

    if (column->nullcount == 0)
        return 0;

    if (column->nullcount == length) {
        cpl_column_fill_double_complex(column, 0, length, code);
        column->nullcount = length;
        return 0;
    }

    dp = cpl_column_get_data_double_complex(column);
    np = cpl_column_get_data_invalid(column);

    for (i = 0; i < length; i++, np++, dp++)
        if (*np == 1)
            *dp = code;

    return CPL_ERROR_NONE;

}
