strbuf_ensure_capacity(StrBuf *sb, uint32_t min_capacity)
{
    if (min_capacity > sb->capacity) {
	sb->capacity = MAX(min_capacity, sb->len*2+2);
    	sb->buf = xrealloc(sb->buf, sb->capacity * sizeof(char));
	if (sb->len == 0)
    	    sb->buf[0] = '\0';
    }
}
