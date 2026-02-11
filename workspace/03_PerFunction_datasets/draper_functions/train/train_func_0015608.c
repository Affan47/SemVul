conjoinv (EBookQueryType type,
          EBookQuery *q,
          va_list ap)
{
	EBookQuery *ret = g_new0 (EBookQuery, 1);
	GPtrArray *qs;

	qs = g_ptr_array_new ();
	while (q) {
		g_ptr_array_add (qs, q);
		q = va_arg (ap, EBookQuery *);
	}

	ret->type = type;
	ret->query.andor.nqs = qs->len;
	ret->query.andor.qs = (EBookQuery **) qs->pdata;
	g_ptr_array_free (qs, FALSE);

	return ret;
}
