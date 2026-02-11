gauss_weight (double freq, int j) {
	double hi, lo;
	lo = (f_info.llambda[j] == -1.0) ? 0.0 : exp (-M_LN2 * pow (freq * f_info.llambda[j], 2.0));
	hi = (f_info.hlambda[j] == -1.0) ? 1.0 : exp (-M_LN2 * pow (freq * f_info.hlambda[j], 2.0));
	return (hi - lo);
}
