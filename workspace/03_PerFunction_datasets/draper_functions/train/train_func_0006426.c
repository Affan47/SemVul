gnm_style_get_pango_attrs (GnmStyle const *style,
			   PangoContext *context,
			   double zoom)
{
	PangoAttrList *l;
	GnmUnderline ul;
	GnmFont *font = gnm_style_get_font (style, context);

	if (style->pango_attrs) {
		if (zoom == style->pango_attrs_zoom) {
			pango_attr_list_ref (style->pango_attrs);
			return style->pango_attrs;
		}
		pango_attr_list_unref (((GnmStyle *)style)->pango_attrs);
	}

	((GnmStyle *)style)->pango_attrs = l = pango_attr_list_new ();
	((GnmStyle *)style)->pango_attrs_zoom = zoom;
	((GnmStyle *)style)->pango_attrs_height = -1;


	if (0) {
		GnmColor const *fore = style->color.font;
		add_attr (l, go_color_to_pango (fore->go_color, TRUE));
	}


	ul = gnm_style_get_font_uline (style);
	if (ul != UNDERLINE_NONE)
		add_attr (l,
			  pango_attr_underline_new (gnm_translate_underline_to_pango (ul)));


	if (gnm_style_get_font_strike (style))
		add_attr (l, pango_attr_strikethrough_new (TRUE));


	switch (gnm_style_get_font_script (style)) {
	default :
	case GO_FONT_SCRIPT_STANDARD :
		break;
	case GO_FONT_SCRIPT_SUB :
		add_attr (l, go_pango_attr_subscript_new (TRUE));
		break;
	case GO_FONT_SCRIPT_SUPER :
		add_attr (l, go_pango_attr_superscript_new (TRUE));
		break;
	}

	add_attr (l, pango_attr_font_desc_new (font->go.font->desc));

	if (zoom != 1)
		add_attr (l, pango_attr_scale_new (zoom));

	pango_attr_list_ref (l);
	return l;
}
