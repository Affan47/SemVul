set_line_style(SCHAR index, ...)
{
	SCHAR count;
	double factor, percentage;
	va_list ap;

	SCHAR val;

	va_start(ap, index);

	for (count = 0, percentage = 0; count < LT_ELEMENTS; count++) {

		val = va_arg(ap, int);

		if (val < 0) {
			break;
		} else {
			lt[index - LT_MIN][count] = (double) val;
			percentage += val;
		}
	}

	lt[index - LT_MIN][count] = -1;

	if (fabs(percentage - 100.) > 0.5) {
		factor = 100.0 / percentage;
		for (count = 0; count < LT_ELEMENTS; count++) {
			if (lt[index - LT_MIN][count] < 0) {
				break;
			} else {
				lt[index - LT_MIN][count] *= factor;
			}
		}
	}

	va_end(ap);

}
