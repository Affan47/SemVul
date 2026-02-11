get_color(const char *spec)
{
	GdkColormap *cmap;
	GdkColor color;

	cmap = gdk_drawable_get_colormap(root->window);
	if (!gdk_color_parse(spec, &color))
		abort();
	if (!gdk_colormap_alloc_color(cmap, &color, FALSE, TRUE))
		abort();
	return color;
}
