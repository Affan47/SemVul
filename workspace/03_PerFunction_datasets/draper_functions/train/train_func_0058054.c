set_with_units(void (*set)(const char *tooltip, const char *fmt, ...),
    const char *prefix, unit_type u, const char *tooltip)
{
	double n;
	int mm;

	switch (curr_unit) {
	case curr_unit_mm:
		n = units_to_mm(u);
		mm = 1;
		break;
	case curr_unit_mil:
		n = units_to_mil(u);
		mm = 0;
		break;
	case curr_unit_auto:
		n = units_to_best(u, &mm);
		break;
	default:
		abort();
	}
	if (mm) {

		set(tooltip, "%s" MM_FORMAT_FIXED " mm", prefix, n);
	} else {

		set(tooltip, "%s" MIL_FORMAT_FIXED " mil", prefix, n);
	}
}
