collapse_arrayref(state * state, AV * queue, AV *markers) {
	int i;
	int mcount = av_len(markers) + 1;
	int qcount = av_len(queue) + 1;
	if (!mcount)
		return;

	AV *close_marker = (AV *)SvRV(*av_fetch(markers, mcount - 1, 0));


	if (*SvPV_nolen(*av_fetch(close_marker, 0, 0)) != ']')
		return;

	int close_index = SvIV(*av_fetch(close_marker, 1, 0));
	if (close_index != qcount) {
		state->mode = ERROR_BRACKET;
		return;
	}

	if (mcount < 2) {
		state->mode = ERROR_BRACKET;
		return;
	}


	AV *open_marker = (AV *)SvRV(*av_fetch(markers, mcount - 2, 0));

	if (*SvPV_nolen(*av_fetch(open_marker, 0, 0)) != '[') {
		state->mode = ERROR_BRACKET;
		return;
	}

	int open_index = SvIV(*av_fetch(open_marker, 1, 0));

	if (open_index > close_index || open_index < 0) {
		state->mode = ERROR_BRACKET;
		return;
	}

	AV * ar = newAV();
	if (close_index > open_index)
		av_extend(ar, close_index - open_index);
	for (i = open_index; i < close_index; i++) {
		SV *e = *av_fetch(queue, i, 0);
		av_push(ar, e);
	}
	for (i = open_index; i < close_index; i++)
		av_pop(queue);

	SvREFCNT_dec(av_pop(markers));
	SvREFCNT_dec(av_pop(markers));

	ar = (AV *) collapse_ref_markers((SV *)ar, queue, markers);
	av_push(queue, newRV_noinc((SV *)ar));
}
