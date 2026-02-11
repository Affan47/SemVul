inprec_rstr (const TCHAR *src)
{
	if (!input_record || !inprec_zf)
		return;
	char *s = uutf8 (src);
	char *ss = s;
	while (*s) {
		inprec_ru8 (*s);
		s++;
	}
	inprec_ru8 (0);
	xfree (ss);
}
