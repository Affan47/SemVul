build_rc_candidates(const uint8_t *values, cdok_set_t *candidates,
				int max)
{
	cdok_set_t rows[CDOK_SIZE] = {0};
	cdok_set_t cols[CDOK_SIZE] = {0};
	int i;


	for (i = 0; i < CDOK_CELLS; i++) {
		uint8_t v = values[i];

		if (v) {
			cdok_set_t s = CDOK_SET_SINGLE(v);

			rows[CDOK_POS_Y(i)] |= s;
			cols[CDOK_POS_X(i)] |= s;
		}
	}


	for (i = 0; i < CDOK_CELLS; i++)
		candidates[i] =
			CDOK_SET_ONES(max) ^
			(rows[CDOK_POS_Y(i)] | cols[CDOK_POS_X(i)]);
}
