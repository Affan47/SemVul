gkrellm_map_color_string(gchar *color_string, GdkColor *color)
	{
	static GdkColormap	*colormap;

	if (colormap == NULL)
		colormap = gtk_widget_get_colormap(top_window);
	if (color->red || color->green || color->blue)
		gdk_colormap_free_colors(colormap, color, 1);
	if (!color_string)
		color_string = "black";
	gdk_color_parse(color_string, color);
	gdk_colormap_alloc_color(colormap, color, FALSE, TRUE);
	}
