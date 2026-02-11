header_append(header_t *o, const char *text, int len)
{
	char buf[MAX_LINE_SIZE];
	const char *p = text;
	uchar c;
	header_field_t *hf;

	header_check(o);
	g_assert(len >= 0);

	if (o->flags & HEAD_F_EOH)
		return HEAD_EOH_REACHED;


	if (len == 0) {
		o->flags |= HEAD_F_EOH;
		return HEAD_EOH;
	}


	if (o->size >= HEAD_MAX_SIZE)
		return HEAD_TOO_LARGE;

	if (++(o->num_lines) >= HEAD_MAX_LINES)
		return HEAD_MANY_LINES;


	c = *p;
	if (is_ascii_space(c)) {


		if (NULL == o->fields)
			return HEAD_CONTINUATION;


		if (o->flags & HEAD_F_SKIP)
			return HEAD_SKIPPED;


		p++;
		while ((c = *p)) {
			if (!is_ascii_space(c))
				break;
			p++;
		}


		if (*p == '\0')
			return HEAD_OK;


		hf = slist_tail(o->fields);
		hfield_append(hf, p);
		add_continuation(o, hf->name, p);
		o->size += len - (p - text);


	} else {
		char *b;
		bool seen_space = FALSE;


		o->flags &= ~HEAD_F_SKIP;


		for (b = buf, c = *p; c; c = *(++p)) {
			if (c == ':') {
				*b++ = '\0';
				break;
			}
			if (is_ascii_space(c)) {
				seen_space = TRUE;
				continue;
			}
			if (
				seen_space || (c != '-' &&
					(!isascii(c) || is_ascii_cntrl(c) || is_ascii_punct(c)))
			) {
				o->flags |= HEAD_F_SKIP;
				return HEAD_BAD_CHARS;
			}
			*b++ = c;
		}


		g_assert(b > buf || (b == buf && *text == '\0'));

		if (b == buf || *(b-1) != '\0') {
			o->flags |= HEAD_F_SKIP;
			return HEAD_MALFORMED;
		}


		hf = hfield_make(buf);


		g_assert(*p == ':');

		p++;
		p = skip_ascii_spaces(p);


		hfield_append(hf, p);
		add_header(o, buf, p);
		if (!o->fields) {
			o->fields = slist_new();
		}
		slist_append(o->fields, hf);
		o->size += len - (p - text);
	}

	return HEAD_OK;
}
