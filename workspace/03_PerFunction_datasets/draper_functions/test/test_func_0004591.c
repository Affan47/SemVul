cpl_array_fill_window_double_complex(cpl_array *array,
                                                    cpl_size start,
                                                    cpl_size count,
                                                    double complex value)
{

    if (array == 0x0)
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);

    if (cpl_column_fill_double_complex(array->column, start, count, value))
        cpl_error_set_where_();

    return CPL_ERROR_NONE;

}
