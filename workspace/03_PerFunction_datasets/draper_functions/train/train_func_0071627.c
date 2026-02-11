text_output(textfile *tf, const wchar_t *s)
{
    char buf[256];
    int ret, len;
    const wchar_t **sp;

    if (!s) {
	sp = NULL;
	len = 1;
    } else {
	sp = &s;
	len = ustrlen(s);
    }

    while (len > 0) {
	ret = charset_from_unicode(sp, &len, buf, lenof(buf),
				   tf->charset, &tf->state, NULL);
	if (!sp)
	    len = 0;
	fwrite(buf, 1, ret, tf->fp);
    }
}
