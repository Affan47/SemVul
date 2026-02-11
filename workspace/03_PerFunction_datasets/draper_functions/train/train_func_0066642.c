print_signals(const char *val, unsigned int base)
{
	int i;
	char *out;

	errno = 0;
        i = strtoul(val, NULL, base);
	if (errno) {
		if (asprintf(&out, "conversion error(%s)", val) < 0)
			out = NULL;
		return out;
	}
	else if (i < 32) {
		const char *s = signal_i2s(i);
		if (s != NULL)
			return strdup(s);
	}
	if (asprintf(&out, "unknown signal (%s%s)",
					base == 16 ? "0x" : "", val) < 0)
		out = NULL;
	return out;
}
