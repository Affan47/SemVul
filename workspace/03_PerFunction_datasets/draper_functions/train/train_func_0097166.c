auparse_get_field_int(auparse_state_t *au)
{
	const char *v = auparse_get_field_str(au);
	if (v) {
		int val;

		errno = 0;
		val = strtol(v, NULL, 10);
		if (errno == 0)
			return val;
	} else
		errno = ENODATA;
	return -1;
}
