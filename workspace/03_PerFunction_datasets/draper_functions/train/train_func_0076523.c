LightenCharColor(char *ColorName, float rate, Display * disp, Window win)
{
	XColor tmp_color;
#ifdef DEBUG
	printf("lightening %s ->", ColorName);
#endif
	tmp_color = ParseColor(ColorName, disp, win);
#ifdef DEBUG
	printf(" #%x %x %x ", tmp_color.red, tmp_color.green, tmp_color.blue);
#endif
	tmp_color.red = tmp_color.red / 257 * rate;
	tmp_color.green = tmp_color.green / 257 * rate;
	tmp_color.blue = tmp_color.blue / 257 * rate;
	if (tmp_color.red > 255)
		tmp_color.red = 255;
	if (tmp_color.green > 255)
		tmp_color.green = 255;
	if (tmp_color.blue > 255)
		tmp_color.blue = 255;
	sprintf(tmp_char, "#%.2x%.2x%.2x",
		(int) tmp_color.red,
		(int) tmp_color.green,
		(int) tmp_color.blue);
#ifdef DEBUG
	printf("-> %s\n", tmp_char);
#endif
	return tmp_char;
}
