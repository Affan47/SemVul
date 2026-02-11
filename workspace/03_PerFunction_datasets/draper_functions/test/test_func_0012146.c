VRT_hashdata(const struct sess *sp, const char *str, ...)
{
	va_list ap;
	const char *p;

	HSH_AddString(sp, str);
	va_start(ap, str);
	while (1) {
		p = va_arg(ap, const char *);
		if (p == vrt_magic_string_end)
			break;
		HSH_AddString(sp, p);
	}
}
