refstrndup(const char *str, size_t len)
{
    char *r;

    if (!str)
	return NULL;

    len = strnlen(str, len);
    r = refstr_alloc(len);
    if (r)
	memcpy(r, str, len);
    return r;
}
