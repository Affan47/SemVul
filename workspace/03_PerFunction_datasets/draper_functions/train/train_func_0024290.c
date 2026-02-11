cconv(Format *format) {
	fmtputc(format, va_arg(format->args, int));
	return FALSE;
}
