_nc_str_init(string_desc * dst, char *src, size_t len)
{
    if (dst != 0) {
	dst->s_head = src;
	dst->s_tail = src;
	dst->s_size = len - 1;
	dst->s_init = dst->s_size;
	if (src != 0)
	    *src = 0;
    }
    return dst;
}
