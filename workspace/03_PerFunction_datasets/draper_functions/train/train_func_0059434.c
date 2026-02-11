compositor_init_svg_glyph(GF_Compositor *compositor, GF_Node *node)
{
	u16 utf_name[20];
	u8 *utf8;
	u32 len;
	GF_Rect rc;
	GF_Glyph *glyph;
	GF_Font *font;
	SVG_GlyphStack *st;
	SVGAllAttributes atts;
	GF_Node *node_font = gf_node_get_parent(node, 0);


	if (node_font) node_font = gf_node_get_parent(node, 0);
	if (!node_font || (gf_node_get_tag(node_font)!=TAG_SVG_font) ) return;
	font = gf_node_get_private(node_font);
	if (!font) return;

	gf_svg_flatten_attributes((SVG_Element*)node, &atts);

	if (gf_node_get_tag(node)==TAG_SVG_missing_glyph) {
		GF_SAFEALLOC(st, SVG_GlyphStack);
		goto reg_common;
	}

	if (!atts.unicode) return;

	GF_SAFEALLOC(st, SVG_GlyphStack);
	utf8 = *atts.unicode;
	len = gf_utf8_mbstowcs(utf_name, 200, (const char **) &utf8);

	if (len==1) {
		st->glyph.utf_name = utf_name[0];
		st->uni_len = 1;
	} else {
		st->glyph.utf_name = (u32) (PTR_TO_U_CAST st);
		st->unicode = gf_malloc(sizeof(u16)*len);
		st->uni_len = len;
		memcpy(st->unicode, utf_name, sizeof(u16)*len);
	}

reg_common:
	st->glyph.ID = (u32) (PTR_TO_U_CAST st);
	st->font = font;
	st->glyph.horiz_advance = font->max_advance_h;
	if (atts.horiz_adv_x) st->glyph.horiz_advance = FIX2INT( gf_ceil(atts.horiz_adv_x->value) );
	if (atts.d) {
		st->glyph.path = atts.d;
		gf_path_get_bounds(atts.d, &rc);
		st->glyph.width = FIX2INT( gf_ceil(rc.width) );
		st->glyph.height = FIX2INT( gf_ceil(rc.height) );
	}
	st->glyph.vert_advance = st->glyph.height;
	if (!st->glyph.vert_advance)
		st->glyph.vert_advance = font->max_advance_v;


	if (!font->glyph) {
		font->glyph = &st->glyph;
	} else {
		glyph = font->glyph;
		while (glyph->next) glyph = glyph->next;
		glyph->next = &st->glyph;
	}

	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, svg_traverse_glyph);
}
