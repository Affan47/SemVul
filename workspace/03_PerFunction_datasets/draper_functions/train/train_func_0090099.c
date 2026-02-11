scale_value(double *value, const char **prefixstr)
{
	double abs_value = fabs(*value);
	double divisor = 1e-9;
	static struct scale_table prefix_scales[] = {
		{1e-6, "n"},
		{1e-3, "u"},
		{1,    "m"},
		{1e3,   ""},
		{1e6,  "k"},
		{1e9,  "M"},
		{0,    "G"},
	};
	struct scale_table *scale = prefix_scales;

	if (abs_value == 0) {
		*prefixstr = "";
		return;
	}

	while (scale->upper_bound && abs_value > scale->upper_bound) {
		divisor = scale->upper_bound;
		scale++;
	}

	*value /= divisor;
	*prefixstr = scale->unit;
}
