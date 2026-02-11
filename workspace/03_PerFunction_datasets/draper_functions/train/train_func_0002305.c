cpl_column_get_data_array_const(const cpl_column *column)
{

    cpl_type type = cpl_column_get_type(column);


    if (column == 0x0) {
        cpl_error_set_where_();
        return NULL;
    }

    if (type & CPL_TYPE_POINTER)
        return (const cpl_array **)column->values->array;

    cpl_error_set_(CPL_ERROR_TYPE_MISMATCH);

    return NULL;

}
