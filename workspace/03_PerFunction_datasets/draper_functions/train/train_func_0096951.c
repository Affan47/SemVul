fz_new_stroke_state_with_len(fz_context *ctx, int len)
{
	fz_stroke_state *state;

	len -= nelem(state->dash_list);
	if (len < 0)
		len = 0;

	state = Memento_label(fz_malloc(ctx, sizeof(*state) + sizeof(state->dash_list[0]) * len), "fz_stroke_state");
	state->refs = 1;
	state->start_cap = FZ_LINECAP_BUTT;
	state->dash_cap = FZ_LINECAP_BUTT;
	state->end_cap = FZ_LINECAP_BUTT;
	state->linejoin = FZ_LINEJOIN_MITER;
	state->linewidth = 1;
	state->miterlimit = 10;
	state->dash_phase = 0;
	state->dash_len = 0;
	memset(state->dash_list, 0, sizeof(state->dash_list[0]) * (len + nelem(state->dash_list)));

	return state;
}
