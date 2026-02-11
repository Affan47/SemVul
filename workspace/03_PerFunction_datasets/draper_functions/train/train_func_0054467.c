path_vfopen(const char *mode, int exit_on_error, const char *path, va_list ap)
{
	FILE *f;
	const char *p = path_vcreate(path, ap);

	f = fopen(p, mode);
	if (!f && exit_on_error)
		err(EXIT_FAILURE, _("error: cannot open %s"), p);
	return f;
}
