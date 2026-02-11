heim_string_create_with_format(const char *fmt, ...)
{
    heim_string_t s;
    char *str = NULL;
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = vasprintf(&str, fmt, ap);
    va_end(ap);
    if (ret < 0 || str == NULL)
	return NULL;

    s = heim_string_ref_create(str, string_dealloc);
    if (s == NULL)
	free(str);
    return s;
}
