cpl_column_get_data_long_long_const(const cpl_column *column)
{

    cpl_type type = cpl_column_get_type(column);


    if (column == 0x0) {
        cpl_error_set_where_();
        return NULL;
    }

    if (type == CPL_TYPE_LONG_LONG)
        return column->values->ll;

    cpl_error_set_(CPL_ERROR_TYPE_MISMATCH);

    return NULL;

}
