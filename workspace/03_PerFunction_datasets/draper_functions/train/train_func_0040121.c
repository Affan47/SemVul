handle_from(const struct strbuf *from)
{
	char *at;
	size_t el;
	struct strbuf f;

	strbuf_init(&f, from->len);
	strbuf_addbuf(&f, from);

	at = strchr(f.buf, '@');
	if (!at) {
		parse_bogus_from(from);
		return;
	}


	if (email.len && strchr(at + 1, '@')) {
		strbuf_release(&f);
		return;
	}


	while (at > f.buf) {
		char c = at[-1];
		if (isspace(c))
			break;
		if (c == '<') {
			at[-1] = ' ';
			break;
		}
		at--;
	}
	el = strcspn(at, " \n\t\r\v\f>");
	strbuf_reset(&email);
	strbuf_add(&email, at, el);
	strbuf_remove(&f, at - f.buf, el + (at[el] ? 1 : 0));


	cleanup_space(&f);
	strbuf_trim(&f);
	if (f.buf[0] == '(' && f.len && f.buf[f.len - 1] == ')') {
		strbuf_remove(&f, 0, 1);
		strbuf_setlen(&f, f.len - 1);
	}

	get_sane_name(&name, &f, &email);
	strbuf_release(&f);
}
