mult_puzzle_num_with_n_digits (gint n) {
	gint result = 0;
	gint32 low = 0;
	gint32 high = 0;
	gdouble _tmp1_;
	gint32 _tmp2_;
	if (n <= 1) {
		low = (gint32) 0;
	} else {
		gdouble _tmp0_;
		_tmp0_ = pow ((gdouble) 10, (gdouble) (n - 1));
		low = (gint32) _tmp0_;
	}
	_tmp1_ = pow ((gdouble) 10, (gdouble) n);
	high = (gint32) _tmp1_;
	_tmp2_ = g_random_int_range (low, high);
	result = (gint) _tmp2_;
	return result;
}
