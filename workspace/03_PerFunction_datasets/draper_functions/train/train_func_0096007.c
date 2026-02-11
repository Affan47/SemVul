fn_year(fs_query *q, fs_value v)
{
    if (v.attr != fs_c.xsd_datetime) {
        return fs_value_error(FS_ERROR_INVALID_TYPE, NULL);
    }
    v = fs_value_fill_lexical(q, v);
    fs_date_fields df;
    if (date_from_iso8601(v.lex, &df)) {
        char *err = g_strdup_printf("cannot get year from xsd:dateTime %s", v.lex);
        fs_query_add_freeable(q, err);

        return fs_value_error(FS_ERROR_INVALID_TYPE, err);
    }

    return fs_value_integer(df.year);
}
