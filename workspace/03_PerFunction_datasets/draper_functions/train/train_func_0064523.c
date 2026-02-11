et_str_nprintf(et_string_t *dest, const char *fmt, ...)
{
    va_list arglist;
    int rv;

    if (dest->buf == NULL)
	return -1;
    va_start(arglist, fmt);
    rv = vsnprintf(dest->buf + dest->pos, dest->bufsize - dest->pos, fmt,
	    arglist);
    if (dest->pos + rv >= dest->bufsize) {
	dest->buf[dest->pos] = '\0';
	va_end(arglist);
	return -1;
    } else {
	dest->pos += rv;
	va_end(arglist);
	return 0;
    }

}
