svg_font_uri_check(GF_Node *node, FontURIStack *st)
{
	GF_Font *font;
	GF_Node *font_elt;
	SVGAllAttributes atts;
	gf_svg_flatten_attributes((SVG_Element*)node, &atts);
	if (!atts.xlink_href) return 0;

	if (atts.xlink_href->type == XMLRI_ELEMENTID) {
		if (!atts.xlink_href->target) atts.xlink_href->target = gf_sg_find_node_by_name(gf_node_get_graph(node), atts.xlink_href->string+1);
	} else {
		GF_SceneGraph *ext_sg;
		char *font_name = strchr(atts.xlink_href->string, '#');
		if (!font_name) return 0;
		if (!st->mo) {
			st->mo = gf_mo_load_xlink_resource(node, 0, 0, -1);
			if (!st->mo) return 0;
		}
		ext_sg = gf_mo_get_scenegraph(st->mo);
		if (!ext_sg) return 0;
		atts.xlink_href->target = gf_sg_find_node_by_name(ext_sg, font_name+1);
		if (!atts.xlink_href->target) return 0;
	}
	font_elt = atts.xlink_href->target;
	if (gf_node_get_tag(font_elt) != TAG_SVG_font) return 0;
	font = gf_node_get_private(font_elt);
	if (!font) return 0;
	st->alias = font;

	gf_mo_is_done(st->mo);
	font->not_loaded = 0;
	return 1;
}
