escape_string(dst_str, src_str)
    char *dst_str, *src_str;
{
    char *src, *dst;

    dst = dst_str;
    for (src = src_str; *src; src++) {
	if (*src == ' ' || *src == '"' || *src == '\'' || *src == '\\')
	  *dst++ = '\\';
	*dst++ = *src;
    }
    *dst = '\0';

    return dst_str;
}
