ReadColor (xmlNodePtr node)
{
	double buf;
	unsigned char red = 0, green = 0, blue = 0, alpha = 0xff;
	if (ReadFloat (node, "red", buf))
		red = buf * 0xff;
	if (ReadFloat (node, "green", buf))
		green = buf * 0xff;
	if (ReadFloat (node, "blue", buf))
		blue = buf * 0xff;
	if (ReadFloat (node, "alpha", buf))
		alpha = buf * 0xff;
	return GO_COLOR_FROM_RGBA (red, green, blue, alpha);
}
