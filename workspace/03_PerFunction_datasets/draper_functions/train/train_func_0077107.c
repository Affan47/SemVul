del_gsvg_state(Graphics_svg_state *gsvg_state) {
	Graphics_svg *gsvg;

	while((gsvg = (Graphics_svg *)list_pop(gsvg_state->svg))) {
		del_gsvg(gsvg);
	}
	del_list(gsvg_state->svg);

  free(gsvg_state->state);
	free(gsvg_state);
}
