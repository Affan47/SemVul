sconv(Format *format) {
	char *s = va_arg(format->args, char *);
	if ((format->flags & FMT_f1set) == 0)
		fmtcat(format, s);
	else {
		size_t len = strlen(s), width = format->f1 - len;
		if (format->flags & FMT_leftside) {
			fmtappend(format, s, len);
			pad(format, width, ' ');
		} else {
			pad(format, width, ' ');
			fmtappend(format, s, len);
		}
	}
	return FALSE;
}
