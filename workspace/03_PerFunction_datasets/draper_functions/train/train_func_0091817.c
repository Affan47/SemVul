parse_number(const char *buf, int *error)
{
	const char *endptr;
	guint64 ret;

	g_assert(buf != NULL);
	g_assert(error != NULL);

	ret = parse_uint64(buf, &endptr, 10, error);
	if (0 == *error && *endptr != '\0') {
		*error = EINVAL;
	}
	if (0 != *error) {
		g_warning("%s(): error with buf=\"%s\"", G_STRFUNC, buf);
		return 0;
	}

	return ret;
}
