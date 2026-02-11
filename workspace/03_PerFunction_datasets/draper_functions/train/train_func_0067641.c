cpl_column_wrap_long_long(long long *data, cpl_size length)
{

    const char *fid = "cpl_column_wrap_long_long";
    cpl_column  *column;


    if (data == 0x0) {
        cpl_error_set(fid, CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    if (length <= 0) {
        cpl_error_set(fid, CPL_ERROR_ILLEGAL_INPUT);
        return NULL;
    }

    column = cpl_column_new(CPL_TYPE_LONG_LONG);

    column->format     = cpl_strdup(LONG_LONG_FORM);
    column->length     = length;
    column->values->ll = data;

    return column;

}
