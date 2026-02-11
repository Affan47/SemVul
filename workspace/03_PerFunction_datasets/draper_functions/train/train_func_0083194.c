ustring_append_ucs4(UString* str, const ucschar* s, gint len)
{
    if (len < 0) {
	const ucschar*p = s;
	while (*p != 0)
	    p++;
	len = p - s;
    }

    return g_array_append_vals(str, s, len);
}
