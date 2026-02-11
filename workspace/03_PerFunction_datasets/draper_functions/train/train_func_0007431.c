it_read_envelope(IT_ENVELOPE *envelope, DUMBFILE *f)
{
	int n;

	envelope->flags = dumbfile_getc(f);
	envelope->n_nodes = dumbfile_getc(f);
	if(envelope->n_nodes > 25) {
		TRACE("IT error: wrong number of envelope nodes (%d)\n", envelope->n_nodes);
		envelope->n_nodes = 0;
		return -1;
	}
	envelope->loop_start = dumbfile_getc(f);
	envelope->loop_end = dumbfile_getc(f);
	envelope->sus_loop_start = dumbfile_getc(f);
	envelope->sus_loop_end = dumbfile_getc(f);
	for (n = 0; n < envelope->n_nodes; n++) {
		envelope->node_y[n] = dumbfile_getc(f);
		envelope->node_t[n] = dumbfile_igetw(f);
	}
	dumbfile_skip(f, 75 - envelope->n_nodes * 3 + 1);

	if (envelope->n_nodes <= 0)
		envelope->flags &= ~IT_ENVELOPE_ON;
	else {
		if (envelope->loop_end >= envelope->n_nodes || envelope->loop_start > envelope->loop_end) envelope->flags &= ~IT_ENVELOPE_LOOP_ON;
		if (envelope->sus_loop_end >= envelope->n_nodes || envelope->sus_loop_start > envelope->sus_loop_end) envelope->flags &= ~IT_ENVELOPE_SUSTAIN_LOOP;
	}

	return dumbfile_error(f);
}
