VRT_WrkString(const struct sess *sp, const char *p, ...)
{
	va_list ap;
	char *b;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	va_start(ap, p);
	b = VRT_String(sp->wrk->ws, NULL, p, ap);
	va_end(ap);
	return (b);
}
