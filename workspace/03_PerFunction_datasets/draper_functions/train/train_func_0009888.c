cpl_column_copy_segment_complex(cpl_column *column,
                                               cpl_size start, cpl_size count,
                                               double complex *values)
{

    const char    *fid    = "cpl_column_copy_segment_complex";
    cpl_size       length = cpl_column_get_size(column);
    cpl_type       type   = cpl_column_get_type(column);
    float complex *fdata;


    if (column == 0x0)
        return cpl_error_set(fid, CPL_ERROR_NULL_INPUT);

    if (start < 0 || start >= length)
        return cpl_error_set(fid, CPL_ERROR_ACCESS_OUT_OF_RANGE);

    if (count <= 0)
        return cpl_error_set(fid, CPL_ERROR_ILLEGAL_INPUT);

    if (count > length - start)
        count = length - start;

    cpl_column_unset_null_segment(column, start, count);

    switch (type) {
    case CPL_TYPE_FLOAT_COMPLEX:
        fdata = cpl_column_get_data_float_complex(column);
        fdata += start;
        while (count--)
            *fdata++ = *values++;
        break;
    case CPL_TYPE_DOUBLE_COMPLEX:
        memcpy(column->values->cd + start, values,
               count * sizeof(double complex));
        break;
    default:
        return cpl_error_set(fid, CPL_ERROR_INVALID_TYPE);
    }

    return CPL_ERROR_NONE;

}
