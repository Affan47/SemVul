visual_get_size_info(GF_TraverseState *tr_state, Fixed *surf_width, Fixed *surf_height)
{
	Fixed w, h;


	w = tr_state->vp_size.x;
	h = tr_state->vp_size.y;

	if (!w || !h) {
		w = INT2FIX(tr_state->visual->compositor->vp_width);
		h = INT2FIX(tr_state->visual->compositor->vp_height);
	}
	if (tr_state->pixel_metrics) {
		*surf_width = w;
		*surf_height = h;
		return 1;
	}
	if (tr_state->min_hsize) {
		*surf_width = gf_divfix(w, tr_state->min_hsize);
		*surf_height = gf_divfix(h, tr_state->min_hsize);
		return 0;
	}
	if (h > w) {
		*surf_width = 2*FIX_ONE;
		*surf_height = gf_divfix(2*h, w);
	} else {
		*surf_width = gf_divfix(2*w, h);
		*surf_height = 2*FIX_ONE;
	}
	return 0;
}
