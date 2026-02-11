svg_apply_text_anchor(GF_TraverseState * tr_state, Fixed *width)
{
	Bool reversed=0;
	if (!tr_state->svg_props->text_anchor) {
		*width = 0;
		return;
	}
	if (*width < 0) {
		*width *= -1;
		reversed = 1;
	}
	switch(*tr_state->svg_props->text_anchor) {
	case SVG_TEXTANCHOR_MIDDLE:
		*width = -(*width)/2;
		break;
	case SVG_TEXTANCHOR_END:
		*width = reversed ? 0 : -(*width);
		break;
	case SVG_TEXTANCHOR_START:
	default:
		*width = reversed ? -(*width) : 0;
		break;
	}
}
