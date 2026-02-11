random_hint(void)
{
	struct hint *v, *r = NULL;
	int n;
	for (v = hints, n = 1; v; v = v->next, n++)
		if (one_in_(n))
			r = v;
	return r->hint;
}
