ht_vasprintf(char **ptr, const char *format, va_list ap)
{
	int ret;

	ret = dopr(NULL, 0, format, ap);
	if (ret <= 0) {
		*ptr = NULL;
		return 0;
	}

	(*ptr) = ht_malloc(ret+1);
	if (!*ptr) return 0;
	ret = ht_vsnprintf(*ptr, ret+1, format, ap);

	return ret;
}
