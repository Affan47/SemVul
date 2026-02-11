is_nan_or_inf(float f) {
	const float INF = strtod("INF", NULL);
	return (enum_is_nan_float(f) || (f == INF) || (f == -INF)) ? 1 : 0;
}
