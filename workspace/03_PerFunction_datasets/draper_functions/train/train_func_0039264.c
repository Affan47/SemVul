ftoa(char *buf, float f, unsigned int digits) {
	int index = 0;
	int exponent;
	long multiplier, whole, part;
	float g;
	char format[16];


	if (f < 0.0f) {
		buf[index++] = '-';
		f = -f;
	}


	if (isinf(f)) {
		strcpy(&buf[index], "INF");
		return 3;
	}

	else if (isnan(f)) {
		strcpy(&buf[index], "NaN");
		return 3;
	} else {

		if (digits > 6) {
			digits = 6;
		}
		multiplier = powf(10.0f, digits);

		if (f > 0.0f) {
			exponent = (int)log10f(f);
		} else {
			exponent = 0;
		}

		g = f / powf(10.0f, exponent);
		if ((g < 1.0f) && (g != 0.0f)) {
			g *= 10.0f;
			exponent--;
		}

		whole = (long)(g);
		part = (long)((g-whole)*multiplier);

		sprintf(format, "%%ld.%%0%dldE%%+.2d", digits);
		sprintf(&buf[index], format, whole, part, exponent);
		return strlen(buf);
	}
}
