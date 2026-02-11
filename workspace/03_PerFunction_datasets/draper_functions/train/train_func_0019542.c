_nc_safe_strcat(string_desc * dst, const char *src)
{
    if (src != 0) {
	size_t len = strlen(src);

	if (len < dst->s_size) {
	    if (dst->s_tail != 0) {
		strcpy(dst->s_tail, src);
		dst->s_tail += len;
	    }
	    dst->s_size -= len;
	    return TRUE;
	}
    }
    return FALSE;
}
