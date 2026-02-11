print_fcntl_cmd(const char *val)
{
	char *out;
	const char *s;
	int cmd;

	errno = 0;
	cmd = strtoul(val, NULL, 16);
        if (errno) {
		if (asprintf(&out, "conversion error(%s)", val) < 0)
			out = NULL;
		return out;
       	}

	s = fcntl_i2s(cmd);
	if (s != NULL)
		return strdup(s);
	if (asprintf(&out, "unknown fcntl command(%d)", cmd) < 0)
		out = NULL;
	return out;
}
