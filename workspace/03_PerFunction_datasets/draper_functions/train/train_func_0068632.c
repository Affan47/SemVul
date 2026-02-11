gf_smil_anim_init_discard(GF_Node *node)
{
	SVGAllAttributes all_atts;
	XLinkAttributesPointers *xlinkp = NULL;
	SVGTimedAnimBaseElement *e = (SVGTimedAnimBaseElement *)node;
	gf_smil_timing_init_runtime_info(node);

	gf_svg_flatten_attributes((SVG_Element *)e, &all_atts);
	GF_SAFEALLOC(e->xlinkp, XLinkAttributesPointers);
	xlinkp = e->xlinkp;
	xlinkp->href = all_atts.xlink_href;
	xlinkp->type = all_atts.xlink_type;

	e->timingp->runtime->evaluate_status = SMIL_TIMING_EVAL_DISCARD;
}
