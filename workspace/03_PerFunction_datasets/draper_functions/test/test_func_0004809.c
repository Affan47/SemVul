cpl_column_delete_but_strings(cpl_column *column)
{

    cpl_type           type;
    cpl_column_values *values;


    if (column == NULL)
        return;

    type = cpl_column_get_type(column);

    if (type == CPL_TYPE_STRING) {
        values = cpl_column_get_values(column);
        if (values) {
            if (values->s)
                cpl_free(values->s);
            cpl_free(values);
        }
        if (column->name)
            cpl_free(column->name);
        if (column->unit)
            cpl_free(column->unit);
        if (column->format)
            cpl_free(column->format);
        if (column->null)
            cpl_free(column->null);
        cpl_free(column);
    }
    else
        cpl_error_set("cpl_column_delete_but_strings", CPL_ERROR_INVALID_TYPE);

}
