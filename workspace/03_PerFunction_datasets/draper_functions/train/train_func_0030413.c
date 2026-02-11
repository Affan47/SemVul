message_is_empty(struct strbuf *sb, int start)
{
	struct strbuf tmpl;
	const char *nl;
	int eol, i;

	if (cleanup_mode == CLEANUP_NONE && sb->len)
		return 0;


	strbuf_init(&tmpl, 0);
	if (template_file && strbuf_read_file(&tmpl, template_file, 0) > 0) {
		stripspace(&tmpl, cleanup_mode == CLEANUP_ALL);
		if (start + tmpl.len <= sb->len &&
		    memcmp(tmpl.buf, sb->buf + start, tmpl.len) == 0)
			start += tmpl.len;
	}
	strbuf_release(&tmpl);


	for (i = start; i < sb->len; i++) {
		nl = memchr(sb->buf + i, '\n', sb->len - i);
		if (nl)
			eol = nl - sb->buf;
		else
			eol = sb->len;

		if (strlen(sign_off_header) <= eol - i &&
		    !prefixcmp(sb->buf + i, sign_off_header)) {
			i = eol;
			continue;
		}
		while (i < eol)
			if (!isspace(sb->buf[i++]))
				return 0;
	}

	return 1;
}
