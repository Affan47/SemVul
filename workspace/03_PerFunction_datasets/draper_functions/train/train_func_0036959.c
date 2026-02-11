draw()
{
	clear(getcolor(palidx_generic_body));
	int c = count();
	for (int i=0; i < c; i++) {
		ht_context_menu *c = get_context_menu(i);
		const char *n = c->get_name();
		const char *s = c->get_shortcut();
		if (i == curmenu) {
			buf->printChar(c->xpos-1, 0, getcolor(palidx_generic_text_selected), ' ');
			buf->print(c->xpos, 0, getcolor(palidx_generic_text_selected), n);
			buf->printChar(c->xpos+strlen(n), 0, getcolor(palidx_generic_text_selected), ' ');
			if (s) buf->printChar(c->xpos+(s - n), 0, getcolor(palidx_generic_text_shortcut_selected), *s);
		} else {
			buf->print(c->xpos, 0, getcolor(palidx_generic_text_focused), n);
			if (s) buf->printChar(c->xpos+(s - n), 0, getcolor(palidx_generic_text_shortcut), *s);
		}
	}
}
