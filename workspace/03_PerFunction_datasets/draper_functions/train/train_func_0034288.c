install_pango_font_map (void)
{
	static GType font_map_type = 0;

	if (!font_map_type) {
		PangoFontMap *font_map;

		font_map = pango_cairo_font_map_get_default ();
		if (!PANGO_IS_FC_FONT_MAP (font_map)) {
			g_warning ("Default pangocairo font map is not a pangofc fontmap. "
				   "Skipping automatic missing-font installation.");
			return;
		}

		font_map_type = pk_pango_fc_font_map_overload_type (G_TYPE_FROM_INSTANCE (font_map));
		font_map = g_object_new (font_map_type, NULL);
		pango_cairo_font_map_set_default (PANGO_CAIRO_FONT_MAP (font_map));
		g_object_unref (font_map);
	}
}
