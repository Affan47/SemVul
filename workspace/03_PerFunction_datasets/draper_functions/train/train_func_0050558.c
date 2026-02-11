print_socketcall(const char *val, unsigned int base)
{
	int a0;
	char *out;
	const char *func = NULL;

	errno = 0;
	a0 = strtol(val, NULL, base);
	if (errno) {
		char *out;
		if (asprintf(&out, "conversion error(%s)", val) < 0)
			out = NULL;
		return out;
	}
	func = sock_i2s(a0);
	if (func)
		return strdup(func);
	else {
		if (asprintf(&out, "unknown socketcall(%d)", val) < 0)
			out = NULL;
                return out;
	}
}
