GMT_zcrit (double alpha)
{
	double sign;


	if (alpha > 0.5) {
		alpha = (1.0 - alpha) * 2.0;
		sign = 1.0;
	}
	else {
		alpha *= 2.0;
		sign = -1.0;
	}

	return (sign * M_SQRT2 * GMT_erfinv (1.0 - alpha));
}
