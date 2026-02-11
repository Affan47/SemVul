reg_found_object(state * state, AV * queue, AV * markers) {
	if (av_len(markers) > -1)
		return 1;
	state->object_counter++;
	if (state->one_object_mode) {
		while(av_len(queue) > 0) {
			SV * dv = av_shift(queue);
			SvREFCNT_dec(dv);
		}
		return 0;
	}
	return 1;
}
