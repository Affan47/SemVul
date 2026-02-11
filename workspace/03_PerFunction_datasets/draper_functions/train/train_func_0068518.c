strbuf_append_ext_header(struct strbuf *sb, const char *keyword,
                                     const char *value, unsigned int valuelen)
{
	char *p;
	int len, total, tmp;


	len = 1 + 1 + strlen(keyword) + 1 + valuelen + 1;
	for (tmp = len; tmp > 9; tmp /= 10)
		len++;

	total = sb->len + len;
	if (total > sb->alloc) {
		sb->buf = xrealloc(sb->buf, total);
		sb->alloc = total;
	}

	p = sb->buf;
	p += sprintf(p, "%u %s=", len, keyword);
	memcpy(p, value, valuelen);
	p += valuelen;
	*p = '\n';
	sb->len = total;
}
