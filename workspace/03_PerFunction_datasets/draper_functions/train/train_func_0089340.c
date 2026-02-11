g_fspc(char *p,
		   struct FONTSPEC *f)
{
	char fname[80];
	int encoding;
	float fsize;

	p = get_str(fname, p, sizeof fname);
	if (isalpha((unsigned char) *p) || *p == '*') {
		if (*p == '*')
			encoding = font_enc[f->fnum];
		else
			encoding = get_encoding(p);
		while (*p != '\0' && !isspace((unsigned char) *p))
			p++;
		while (isspace((unsigned char) *p))
			p++;
	} else {
		encoding = -1;
	}
	fsize = f->size;
	if (*p != '\0' && *p != '*') {
		char *q;
		float v;

		v = strtod(p, &q);
		if (v <= 0 || (*q != '\0' && *q != ' '))
			error(1, 0, "Bad font size '%s'", p);
		else
			fsize = v;
	}
	fontspec(f,
		 strcmp(fname, "*") != 0 ? fname : 0,
		 encoding,
		 fsize);
	if (!file_initialized)
		used_font[f->fnum] = 1;
	if (f - cfmt.font_tb == outft)
		outft = -1;
#ifdef HAVE_PANGO
	pg_reset_font();
#endif
}
