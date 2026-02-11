xls_read_pivot_cache_values (XLSReadPivot *s, BiffQuery *q, unsigned int n, const char *type)
{

	GPtrArray *res = g_ptr_array_sized_new (n);
	GnmValue *v;
	unsigned int i;

	d (1, g_printerr ("/* %u %s items */ ;\n", n, type););
	for (i = 0 ; i < n ; i++) {
		if (NULL == (v = xls_read_pivot_cache_value (s, q))) {

			g_ptr_array_set_size (res, i);
			return res;
		}

		g_ptr_array_add (res, v);
	}
	return res;
}
