parser_getval(struct parser *p, const char *name) {
	struct parser_value *v;
	for (v = p->fhead; v; v = (struct parser_value *)v->spec.next)
	{
		if (!strcmp(v->spec.name, name))
		{
			return v;
		}
	}
	assert(0);
}
