color_from_string (const char *string,
		   GdkColor   *colorp)
{

	gdk_color_parse ("black", colorp);

	if (!string)
		return;

	gdk_color_parse (string, colorp);
}
