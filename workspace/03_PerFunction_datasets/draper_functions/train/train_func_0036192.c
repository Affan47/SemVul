tn3270e_current_opts(void)
{
	int i;
	static char text_buf[1024];
	char *s = text_buf;

	if (!e_funcs || !IN_E)
		return CN;
	for (i = 0; i < 32; i++) {
		if (e_funcs & E_OPT(i))
		s += sprintf(s, "%s%s", (s == text_buf) ? "" : " ",
		    fnn(i));
	}
	return text_buf;
}
