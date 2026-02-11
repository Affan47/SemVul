vector_sum_double(const double* v, size_t n) {
	double w = 0;
	size_t i;
	for (i = 0; i < n; i++)
		w += v[i];
	return w;
}
