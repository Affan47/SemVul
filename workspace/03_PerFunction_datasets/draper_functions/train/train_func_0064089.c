put_history(void)
{
	struct SYMBOL *s, *s2;
	int font;
	unsigned u;
	float w, h;
	char tmp[265];

	font = 0;
	for (s = info['I' - 'A']; s != 0; s = s->next) {
		u = s->as.text[0] - 'A';
		if (!(cfmt.fields[0] & (1 << u))
		 || (s2 = info[u]) == 0)
			continue;
		if (!font) {
			bskip(cfmt.textspace);
			str_font(HISTORYFONT);
			font = 1;
		}
		get_str(tmp, &s->as.text[1], sizeof tmp);
		w = tex_str(tmp);
		h = cfmt.font_tb[HISTORYFONT].size * cfmt.lineskipfac;
		set_font(HISTORYFONT);
		PUT1("0 0 M(%s)show ", tex_buf);
		for (;;) {
			put_inf(s2);
			if ((s2 = s2->next) == 0)
				break;
			bskip(h);
			a2b("%.2f 0 M ", w);
		}
		bskip(h * 1.2);
		buffer_eob();
	}
}
