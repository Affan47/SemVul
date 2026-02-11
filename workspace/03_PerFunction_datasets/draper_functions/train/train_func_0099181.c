out_size(struct formatter *f, uint64_t size, const char *fmt, ...)
{
	char buffer[64];
	va_list ap;
	int r;

	if (!_sectors_to_units(size, buffer, sizeof(buffer)))
		return 0;

	_out_with_comment(f, buffer, fmt, ap);

	return r;
}
