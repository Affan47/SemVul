_gda_row_hash (gconstpointer key)
{
	gint i, len;
	GdaRow *r;
	guint res = 0;
	r = (GdaRow*) key;
	len = gda_row_get_length (r);
	for (i = 0; i < len ; i++) {
		GValue *v;
		v = gda_row_get_value (r, i);
		res = (res << 5) + res + _gda_value_hash (v);
	}
	return res;
}
