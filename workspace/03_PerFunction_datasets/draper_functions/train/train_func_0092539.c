oo_parse_border (GsfXMLIn *xin, GnmStyle *style,
		 xmlChar const *str, GnmStyleElement location)
{
	double pts;
	char const *end = oo_parse_distance (xin, str, "border", &pts);
	GnmBorder *border = NULL;
	GnmColor *color = NULL;
	const char *border_color = NULL;
	GnmStyleBorderType border_style;
	GnmStyleBorderLocation const loc =
		GNM_STYLE_BORDER_TOP + (int)(location - MSTYLE_BORDER_TOP);

	if (end == NULL || end == CXML2C (str))
		return;
	while (*end == ' ')
		end++;

	border_color = strchr (end, '#');
	if (border_color) {
		char *border_type = g_strndup (end, border_color - end);
		color = oo_parse_color (xin, CC2XML (border_color), "color");

		if (color) {
			if (g_str_has_prefix (border_type, "none")||
			    g_str_has_prefix (border_type, "hidden"))
				border_style = GNM_STYLE_BORDER_NONE;
			else if (g_str_has_prefix (border_type, "solid") ||
				 g_str_has_prefix (border_type, "groove") ||
				 g_str_has_prefix (border_type, "ridge") ||
				 g_str_has_prefix (border_type, "inset") ||
				 g_str_has_prefix (border_type, "outset")) {
				if (pts <= OD_BORDER_THIN)
					border_style = GNM_STYLE_BORDER_THIN;
				else if (pts <= OD_BORDER_MEDIUM)
					border_style = GNM_STYLE_BORDER_MEDIUM;
				else
					border_style = GNM_STYLE_BORDER_THICK;
			} else if (g_str_has_prefix (border_type, "dashed"))
				border_style = GNM_STYLE_BORDER_DASHED;
			else if (g_str_has_prefix (border_type, "dotted"))
				border_style = GNM_STYLE_BORDER_DOTTED;
			else
				border_style = GNM_STYLE_BORDER_DOUBLE;

			border = gnm_style_border_fetch (border_style, color,
							 gnm_style_border_get_orientation (loc));
			border->width = pts;
			gnm_style_set_border (style, location, border);
		}
		g_free (border_type);
	}
}
