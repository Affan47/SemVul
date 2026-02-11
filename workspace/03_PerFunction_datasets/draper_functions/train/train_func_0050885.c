compositor_svg_traverse_base(GF_Node *node, SVGAllAttributes *atts, GF_TraverseState *tr_state,
					 SVGPropertiesPointers *backup_props, u32 *backup_flags)
{
	u32 inherited_flags_mask, flags;

	if (atts->requiredFeatures || atts->requiredExtensions || atts->systemLanguage
	|| atts->requiredFonts || atts->requiredFormats) {
		if (!compositor_svg_evaluate_conditional(tr_state->visual->compositor, atts))
			return 0;
	}

	memcpy(backup_props, tr_state->svg_props, sizeof(SVGPropertiesPointers));
	*backup_flags = tr_state->svg_flags;

#if 0

	inherited_flags_mask = gf_svg_apply_inheritance(atts, tr_state->svg_props);
	gf_svg_apply_animations(node, tr_state->svg_props);
#else

	gf_svg_apply_animations(node, tr_state->svg_props);
	inherited_flags_mask = gf_svg_apply_inheritance(atts, tr_state->svg_props);


#endif
	tr_state->svg_flags &= inherited_flags_mask;
	flags = gf_node_dirty_get(node);
	tr_state->svg_flags |= flags;

	return 1;
}
