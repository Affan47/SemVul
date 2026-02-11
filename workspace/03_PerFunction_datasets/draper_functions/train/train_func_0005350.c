grecs_error(grecs_locus_t const *locus, int errcode, const char *fmt, ...)
{
	va_list ap;
	char *buf = NULL;
	size_t size = 0;

	va_start(ap, fmt);
	if (grecs_vasprintf(&buf, &size, fmt, ap))
		grecs_alloc_die();
	va_end(ap);
	grecs_print_diag_fun(locus, 1, errcode, buf);
	free(buf);
	grecs_error_count++;
}
