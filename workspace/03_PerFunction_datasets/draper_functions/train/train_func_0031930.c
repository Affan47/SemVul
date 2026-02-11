do_once_cb(void *priv, const struct VSC_point * const pt)
{
	struct once_priv *op;
	uint64_t val;
	int i;

	op = priv;
	assert(!strcmp(pt->fmt, "uint64_t"));
	val = *(const volatile uint64_t*)pt->ptr;
	i = 0;
	if (strcmp(pt->class, ""))
		i += printf("%s.", pt->class);
	if (strcmp(pt->ident, ""))
		i += printf("%s.", pt->ident);
	i += printf("%s", pt->name);
	if (i > op->pad)
		op->pad = i + 1;
	printf("%*.*s", op->pad - i, op->pad - i, "");
	if (pt->flag == 'a')
		printf("%12ju %12.2f %s\n", val, val / op->up, pt->desc);
	else
		printf("%12ju %12s %s\n", val, ".  ", pt->desc);
	return (0);
}
