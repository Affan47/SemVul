UpdateYIQTableFromExternal(double yiq_table[768], double start_angle, const double start_saturation)
{
	const double gamma = 1 - COLOURS_NTSC_setup.gamma / 2.0;
	unsigned char *ext_ptr = COLOURS_NTSC_external.palette;
	int n;

	start_angle = - colorburst_angle - start_angle;

	for (n = 0; n < 256; n ++) {

		double r = (double)*ext_ptr++ / 255.0;
		double g = (double)*ext_ptr++ / 255.0;
		double b = (double)*ext_ptr++ / 255.0;
		double y = 0.299 * r + 0.587 * g + 0.114 * b;
		double i = 0.595716 * r - 0.274453 * g - 0.321263 * b;
		double q = 0.211456 * r - 0.522591 * g + 0.311135 * b;
		double s = sin(start_angle);
		double c = cos(start_angle);
		double tmp_i = i;
		i = tmp_i * c - q * s;
		q = tmp_i * s + q * c;

		if (COLOURS_NTSC_external.adjust) {
			y = pow(y, gamma);
			y *= COLOURS_NTSC_setup.contrast * 0.5 + 1;
			y += COLOURS_NTSC_setup.brightness * 0.5;
			if (y > 1.0)
				y = 1.0;
			else if (y < 0.0)
				y = 0.0;
			i *= start_saturation + 1;
			q *= start_saturation + 1;
		}

		*yiq_table++ = y;
		*yiq_table++ = i;
		*yiq_table++ = q;
	}
}
