skipWhitespaceComment(LexAccessor &styler, unsigned int &p) {

	int style;
	while ((p > 0) && (style = styler.StyleAt(p),
	        style == SCE_PL_DEFAULT || style == SCE_PL_COMMENTLINE))
		p--;
}
