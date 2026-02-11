strbuf_free_to_substring(StrBuf *sb, int32_t sp, int32_t ep)
{
    char *buf;

    sp = normalize_strbuf_pos(sb, sp);
    ep = normalize_strbuf_pos(sb, ep);
    if (sp != 0)
	memmove(sb->buf, sb->buf+sp, ep-sp);
    sb->buf[ep-sp] = '\0';


    if (sp == 0 && ep == sb->len)
	buf = sb->buf;
    else
	buf = xrealloc(sb->buf, ep-sp+1);
    free(sb);
    return buf;
}
