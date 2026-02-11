isl_printer_set_indent_prefix(__isl_take isl_printer *p,
	const char *prefix)
{
	if (!p)
		return NULL;

	free(p->indent_prefix);
	p->indent_prefix = prefix ? strdup(prefix) : NULL;

	return p;
}
