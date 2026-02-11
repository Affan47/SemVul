strip_module_symbol_end(char *buf)
{
	char *p1, *lastR;

	if (!(lastR = strrchr(buf, 'R')))
		return;

	if (((p1 = lastR-1) < buf) || (*p1 != '_'))
		return;

	if ((kt->flags & SMP) && STRNEQ(p1, "_Rsmp_")) {
		*p1 = NULLCHAR;
		return;
	}

	if (!hexadecimal(lastR+1, 0))
		return;

	*p1 = NULLCHAR;
}
