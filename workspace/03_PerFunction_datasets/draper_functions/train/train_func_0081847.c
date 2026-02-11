cpl_column_has_invalid(cpl_column *column)
{

    cpl_type type   = cpl_column_get_type(column);
    cpl_size length = cpl_column_get_size(column);


    if (column == 0x0) {
        cpl_error_set_where("cpl_column_has_invalid");
        return -1;
    }

    if (type == CPL_TYPE_STRING) {
        while (length--)
            if (column->values->s[length] == NULL)
                return 1;
        return 0;
    }
    if (type & CPL_TYPE_POINTER) {
        while (length--)
            if (column->values->array[length] == NULL)
                return 1;
        return 0;
    }

    return (column->nullcount > 0 ? 1 : 0);

}
