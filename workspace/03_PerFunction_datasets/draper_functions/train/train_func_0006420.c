_handle_long(s_p_values_t *v,
			const char *value, const char *line, char **leftover)
{
	if (v->data_count != 0) {
		error("%s specified more than once, latest value used",
		      v->key);
		xfree(v->data);
		v->data_count = 0;
	}

	if (v->handler != NULL) {

		int rc;
		rc = v->handler(&v->data, v->type, v->key, value,
				line, leftover);
		if (rc != 1)
			return rc == 0 ? 0 : -1;
	} else {
		char *endptr;
		long num;
		errno = 0;
		num = strtol(value, &endptr, 0);
		if ((num == 0 && errno == EINVAL)
		    || (*endptr != '\0')) {
			if (strcasecmp(value, "UNLIMITED") == 0
			    || strcasecmp(value, "INFINITE") == 0) {
				num = (long) INFINITE;
			} else {
				error("\"%s\" is not a valid number", value);
				return -1;
			}
		} else if (errno == ERANGE) {
			error("\"%s\" is out of range", value);
			return -1;
		}
		v->data = xmalloc(sizeof(long));
		*(long *)v->data = num;
	}

	v->data_count = 1;
	return 1;
}
