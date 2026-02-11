gabedit_cairo_string(cairo_t* cr, GtkWidget* parent, PangoFontDescription *font_desc, GdkGC* gc , gint x, gint y, G_CONST_RETURN gchar* str, gboolean centerX, gboolean centerY)
{
	int width  = 0;
	int height = 0;
	PangoStyle style = pango_font_description_get_style(font_desc);;
	cairo_font_slant_t cairoStyle = CAIRO_FONT_SLANT_NORMAL;
	G_CONST_RETURN gchar *name = pango_font_description_get_family (font_desc);
	PangoWeight weight = pango_font_description_get_weight(font_desc);
	cairo_font_weight_t cairoWeight = PANGO_WEIGHT_NORMAL;
	gint fontSize = pango_font_description_get_size (font_desc)/PANGO_SCALE;
	GdkGCValues values;
	GdkColormap *colormap;
	GdkColor color;

	cairo_save (cr);
	gdk_gc_get_values(gc, &values);
   	colormap  = gdk_drawable_get_colormap(parent->window);
        gdk_colormap_query_color(colormap, values.foreground.pixel,&color);

	switch(style)
	{
		case PANGO_STYLE_NORMAL:  cairoStyle = CAIRO_FONT_SLANT_NORMAL;break;
		case PANGO_STYLE_OBLIQUE: cairoStyle = CAIRO_FONT_SLANT_OBLIQUE;break;
		case PANGO_STYLE_ITALIC : cairoStyle = CAIRO_FONT_SLANT_ITALIC;break;
	}
	switch(weight)
	{
		case PANGO_WEIGHT_ULTRALIGHT:
		case PANGO_WEIGHT_LIGHT:
		case PANGO_WEIGHT_NORMAL:
			cairoWeight = PANGO_WEIGHT_NORMAL;
			break;
		case PANGO_WEIGHT_SEMIBOLD:
		case PANGO_WEIGHT_BOLD:
		case PANGO_WEIGHT_ULTRABOLD:
		case PANGO_WEIGHT_HEAVY:
			cairoWeight = CAIRO_FONT_WEIGHT_BOLD;
	}

	height = fontSize;
	width = fontSize*strlen(str);
	if(centerX) x -= width/4;
	if(centerY) y += height/4;
	cairo_select_font_face (cr, name, cairoStyle, cairoWeight);
	gdk_cairo_set_source_color (cr, &color);
        cairo_set_font_size (cr, fontSize);
	cairo_move_to (cr, x, y);
	cairo_show_text (cr, str);
	cairo_stroke (cr);
	cairo_restore (cr);
}
