fn_datetime_equal(fs_query *q, fs_value a, fs_value b)
{
    if (a.attr == fs_c.xsd_datetime && b.attr == fs_c.xsd_datetime &&
        (a.in != -1 || b.in != -1))
	return fs_value_boolean(a.in == b.in);

    if (a.lex && b.lex) {
        return fs_value_boolean(iso8601_compare(a.lex, b.lex) == 0);
    }

    return fs_value_error(FS_ERROR_INVALID_TYPE, "bad arguments to fn:datetime-equal");
}
