go_line_interpolation_as_str (GOLineInterpolation type)
{
	unsigned i;
	char const *ret = "linear";

	for (i = 0; i < G_N_ELEMENTS (line_interpolations); i++) {
		if (line_interpolations[i].type == type) {
			ret = line_interpolations[i].name;
			break;
		}
	}
	return ret;
}
