readui(const char **sp, const char *e, readui_base base) {
	const char *s = *sp;

	while (s<e && cwhite(*s)) s++;
	e = skipnum(s, e, base);

	*sp = e;
	return readui_valid(s, e, base);
}
