cpl_column_fill_invalid_cplsize(cpl_column *column,
                                               cpl_size code)
{

    const char *fid    = "cpl_column_fill_invalid_cplsize";
    cpl_type    type   = cpl_column_get_type(column);
    cpl_size    length = cpl_column_get_size(column);
    int        *np;
    cpl_size   *lp;
    cpl_size    i;
    cpl_column *acolumn;


    if (column == 0x0)
        return cpl_error_set(fid, CPL_ERROR_NULL_INPUT);

    if (!(type & CPL_TYPE_SIZE))
        return cpl_error_set(fid, CPL_ERROR_TYPE_MISMATCH);

    if (type & CPL_TYPE_POINTER) {

        cpl_array **array = cpl_column_get_data_array(column);

        while (length--) {
            if (array[length] == NULL)
                array[length] = cpl_array_new(column->depth, CPL_TYPE_SIZE);
            acolumn = cpl_array_get_column(array[length]);
            cpl_column_fill_invalid_cplsize(acolumn, code);
        }
        return CPL_ERROR_NONE;
    }

    if (column->nullcount == 0)
        return CPL_ERROR_NONE;

    if (column->nullcount == length) {
        cpl_column_fill_cplsize(column, 0, length, code);
        column->nullcount = length;
        return CPL_ERROR_NONE;
    }

    lp = cpl_column_get_data_cplsize(column);
    np = cpl_column_get_data_invalid(column);

    for (i = 0; i < length; i++, np++, lp++)
        if (*np == 1)
            *lp = code;

    return CPL_ERROR_NONE;

}
