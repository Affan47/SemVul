mult_puzzle_expand_num_string (MultPuzzle* self, gchar** n, gsize minimum) {
	gint _tmp0_;
	gint _tmp1_;
	gsize difference;
	GString* _tmp2_ = NULL;
	GString* rv;
	gchar* _tmp4_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (n != NULL);
	_tmp0_ = strlen (*n);
	if (_tmp0_ >= minimum) {
		return;
	}
	_tmp1_ = strlen (*n);
	difference = minimum - _tmp1_;
	_tmp2_ = g_string_new ("");
	rv = _tmp2_;
	{
		gsize i;
		i = (gsize) 0;
		{
			gboolean _tmp3_;
			_tmp3_ = TRUE;
			while (TRUE) {
				if (!_tmp3_) {
					i = i + 1;
				}
				_tmp3_ = FALSE;
				if (!(i < difference)) {
					break;
				}
				g_string_append_c (rv, '0');
			}
		}
	}
	g_string_append (rv, *n);
	_tmp4_ = g_strdup (rv->str);
	_g_free0 (*n);
	*n = _tmp4_;
	_g_string_free0 (rv);
}
