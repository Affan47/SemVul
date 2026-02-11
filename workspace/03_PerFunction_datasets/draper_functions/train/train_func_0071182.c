strbuf_new_with_capacity(uint32_t capacity)
{
    StrBuf *sb;
    sb = xmalloc(sizeof(StrBuf));
    sb->len = 0;
    sb->capacity = capacity;
    sb->buf = xmalloc(sb->capacity * sizeof(char));
    if (sb->capacity > 0)
    	sb->buf[0] = '\0';
    return sb;
}
