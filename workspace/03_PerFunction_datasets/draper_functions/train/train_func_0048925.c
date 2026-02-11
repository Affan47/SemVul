get_colorstring (GdkColor *tcolor)
{
	guint r, g, b;
	gchar *cstring;

	r = tcolor->red / 256;
	g = tcolor->green / 256;
	b = tcolor->blue / 256;

	cstring = g_malloc (sizeof (gchar)*7+1);
	g_snprintf (cstring, 8, "#%02x%02x%02x", r, g, b);

	if (mydebug > 20)
		fprintf (stderr, "get_colorstring result: %s\n", cstring);

	return cstring;
}
