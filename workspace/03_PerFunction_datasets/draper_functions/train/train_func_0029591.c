gimp_hsl_value (gdouble n1,
                gdouble n2,
                gdouble hue)
{
	gdouble value;

	if (hue > 255)
		hue -= 255;
	else if (hue < 0)
		hue += 255;

	if (hue < 42.5)
		value = n1 + (n2 - n1) * (hue / 42.5);
	else if (hue < 127.5)
		value = n2;
	else if (hue < 170)
		value = n1 + (n2 - n1) * ((170 - hue) / 42.5);
	else
		value = n1;

	return value * 255.0;
}
