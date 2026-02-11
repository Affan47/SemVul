svg_traverse_defs(GF_Node *node, void *rs, Bool is_destroy)
{
	SVGPropertiesPointers backup_props;
	u32 prev_flags, backup_flags;
	u32 styling_size = sizeof(SVGPropertiesPointers);

	GF_TraverseState *tr_state = (GF_TraverseState *) rs;

	SVGAllAttributes all_atts;

	if (is_destroy) {
		gf_sc_check_focus_upon_destroy(node);
		return;
	}
	gf_svg_flatten_attributes((SVG_Element *)node, &all_atts);

	if (!compositor_svg_traverse_base(node, &all_atts, tr_state, &backup_props, &backup_flags))
		return;

	prev_flags = tr_state->switched_off;
	tr_state->switched_off = 1;
	compositor_svg_traverse_children(((SVG_Element *)node)->children, tr_state);
	tr_state->switched_off = prev_flags;

	memcpy(tr_state->svg_props, &backup_props, styling_size);
	tr_state->svg_flags = backup_flags;
}
