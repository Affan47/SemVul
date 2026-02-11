write_title(struct SYMBOL *s)
{
	char *p;

	p = &s->as.text[2];
	if (*p == '\0')
		return;
	p = trim_title(p, s == info['T' - 'A']);
	if (s == info['T' - 'A']) {
		bskip(cfmt.titlespace + cfmt.font_tb[TITLEFONT].size);
		str_font(TITLEFONT);
	} else {
		bskip(cfmt.subtitlespace + cfmt.font_tb[SUBTITLEFONT].size);
		str_font(SUBTITLEFONT);
	}
	if (cfmt.titleleft)
		PUT0("0 0 M ");
	else
		PUT1("%.1f 0 M ",
		     0.5 * ((cfmt.landscape ? cfmt.pageheight : cfmt.pagewidth)
		     - cfmt.leftmargin - cfmt.rightmargin) / cfmt.scale);
	put_str(p, cfmt.titleleft ? A_LEFT : A_CENTER);
}
