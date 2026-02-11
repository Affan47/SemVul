seen_attr(struct htmlfilter_info *p,
			const unicode_char *uc,
			size_t cnt)
{
	if (SPACE(*uc))
		return 1;

	if (*uc == '/')
	{
		p->tag_empty=1;
		return 1;
	}

	if (isualnum(*uc))
	{
		unicode_buf_clear(&p->atom);
		p->handler_func=seen_attrname;
		return seen_attrname(p, uc, cnt);
	}

	p->handler_func=handle_chars;

	if (*uc == '>')
		open_element(p);

	return 1;
}
