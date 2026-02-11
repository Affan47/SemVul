isl_printer_free(__isl_take isl_printer *p)
{
	if (!p)
		return NULL;
	free(p->buf);
	free(p->indent_prefix);
	free(p->prefix);
	free(p->suffix);
	isl_ctx_deref(p->ctx);
	free(p);

	return NULL;
}
