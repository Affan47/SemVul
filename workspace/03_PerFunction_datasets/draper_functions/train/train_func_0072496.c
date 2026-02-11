brcmu_dbg_hex_dump(const void *data, size_t size, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_debug("%pV", &vaf);

	va_end(args);

	print_hex_dump_bytes("", DUMP_PREFIX_OFFSET, data, size);
}
