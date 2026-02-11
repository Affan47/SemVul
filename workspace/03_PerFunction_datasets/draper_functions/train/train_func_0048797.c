heim_error_createv(int error_code, const char *fmt, va_list ap)
{
    heim_error_t e;
    char *str;
    int len;

    str = malloc(1024);
    if (str == NULL)
        return NULL;
    len = vsnprintf(str, 1024, fmt, ap);
    if (len < 0) {
        free(str);
	return NULL;
    }

    e = _heim_alloc_object(&_heim_error_object, sizeof(struct heim_error));
    if (e) {
	e->msg = heim_string_create(str);
	e->error_code = error_code;
    }
    free(str);

    return e;
}
