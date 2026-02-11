collapse_hashref(state * state, AV * queue, AV *markers) {
	int i;
	int mcount = av_len(markers) + 1;
	int qcount = av_len(queue) + 1;
	if (!mcount)
		return;

	AV *close_marker = (AV *)SvRV(*av_fetch(markers, mcount - 1, 0));


	if (*SvPV_nolen(*av_fetch(close_marker, 0, 0)) != '}')
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

	if (*SvPV_nolen(*av_fetch(open_marker, 0, 0)) != '{') {
		state->mode = ERROR_BRACKET;
		return;
	}

	int open_index = SvIV(*av_fetch(open_marker, 1, 0));

	if (open_index > close_index || open_index < 0) {
		state->mode = ERROR_BRACKET;
		return;
	}


	if ((close_index - open_index) % 2) {
		av_push(queue, newSV(0));
		close_index++;
	}

	HV * hr = newHV();
	for (i = open_index; i < close_index; i+= 2) {
		SV *k = * av_fetch(queue, i, 0);
		SV *v = * av_fetch(queue, i + 1, 0);


		if (!SvOK(k))
			sv_setpvn(k, "", 0);

		if (hv_exists_ent(hr, k, 0)) {
			STRLEN keylen;
			char * key = SvPV(k, keylen);
			sv_setsv(*hv_fetch(hr, key, keylen, 0), v);
			SvREFCNT_dec(v);
		} else {
			(void) hv_store_ent(hr, k, v, 0);
		}
		SvREFCNT_dec(k);
	}
	for (i = open_index; i < close_index; i++)
		av_pop(queue);

	SvREFCNT_dec(av_pop(markers));
	SvREFCNT_dec(av_pop(markers));

	hr = (HV *) collapse_ref_markers((SV *)hr, queue, markers);
	av_push(queue, newRV_noinc((SV *)hr));
}
