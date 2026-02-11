lotus_read (LotusState *state)
{
	record_t r;
	r.input = state->input;

	if (!record_next (&r)) return FALSE;

	if (r.len < 2)
		return FALSE;

	state->version = GSF_LE_GET_GUINT16 (r.data);

	if (r.type == LOTUS_BOF) {
		state->is_works = FALSE;
#if LOTUS_DEBUG > 0
		g_printerr ("Version=%x, Lotus\n", state->version);
#endif
		switch (state->version) {
		case LOTUS_VERSION_ORIG_123:
		case LOTUS_VERSION_SYMPHONY:
		case LOTUS_VERSION_SYMPHONY2:
			return lotus_read_old (state, &r);

		default:
			g_warning ("Unexpected version %x", state->version);

		case LOTUS_VERSION_123V4:
		case LOTUS_VERSION_123V6:
		case LOTUS_VERSION_123V7:
		case LOTUS_VERSION_123SS98:
			return lotus_read_new (state, &r);
		}
	} else if (r.type == WORKS_BOF) {
		state->is_works = TRUE;
#if LOTUS_DEBUG > 0
		g_printerr ("Version=%x, MS Works\n", state->version);
#endif
		if (state->version == WORKS_VERSION_3)
			return lotus_read_works (state, &r);
	}

	return FALSE;
}
