fs_value_datetime_from_string(const char *s)
{
    fs_value v = fs_value_blank();
    v.attr = fs_c.xsd_datetime;

    struct tm td;

    memset(&td, 0, sizeof(struct tm));

    time_t utc;
    if (fs_time_from_iso8601(s, &utc)) {
        v.in = utc;
        v.valid = fs_valid_bit(FS_V_IN);
        v.lex = (char *)s;

        return v;
    }
    char *ret = strptime(s, "%Y-%m-%d", &td);
    if (ret) {
	v.in = timegm(&td);
	v.valid = fs_valid_bit(FS_V_IN);

	return v;
    }

    return fs_value_error(FS_ERROR_INVALID_TYPE,
	    "cannot convert value to xsd:dateTime");
}
