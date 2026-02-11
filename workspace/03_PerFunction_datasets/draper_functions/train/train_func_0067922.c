lazy_opts(B *b, OPTIONS *o)
{
	o->syntax = load_syntax(o->syntax_name);
	if (!o->map_name) {

		unsigned char buf[1024];
		int len = 1024;
		if (b->eof->byte < 1024)
			len = b->eof->byte;
		brmem(b->bof, buf, len);
		o->charmap = guess_map(buf, len);
		o->map_name = zdup(o->charmap->name);
	} else {
		o->charmap = find_charmap(o->map_name);
	}
	if (!o->charmap)
		o->charmap = locale_map;
	if (!o->language)
		o->language = zdup(locale_msgs);

	if (o->hex && o->charmap->type) {
		o->charmap = find_charmap(USTR "c");
	}
}
