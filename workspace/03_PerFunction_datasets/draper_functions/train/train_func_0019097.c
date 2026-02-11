init_ppp48_idx (void)

{
	enum  {MAX_I = 48, MAX_J = 48, MAX_K = 48};
	SQUARE i, j, k;
	index_t idx = 0;
	SQUARE a, b, c;
	int x, y, z;


	for (i = 0; i < MAX_I; i++) {
		for (j = 0; j < MAX_J; j++) {
			for (k = 0; k < MAX_K; k++) {
				IDX_set_empty(ppp48_idx [i][j][k]);
			}
		}
	}

	for (idx = 0; idx < MAX_PPP48_INDEX; idx++) {
		ppp48_sq_x [idx] = (uint8_t)NOSQUARE;
		ppp48_sq_y [idx] = (uint8_t)NOSQUARE;
		ppp48_sq_z [idx] = (uint8_t)NOSQUARE;
	}

	idx = 0;
	for (x = 0; x < 48; x++) {
		for (y = x+1; y < 48; y++) {
			for (z = y+1; z < 48; z++) {

				a = itosq [x];
				b = itosq [y];
				c = itosq [z];

				if (!in_queenside(b) || !in_queenside(c))
						continue;

				i = a - 8;
				j = b - 8;
				k = c - 8;

				if (IDX_is_empty(ppp48_idx [i] [j] [k])) {

					ppp48_idx  [i][j][k] = idx;
					ppp48_idx  [i][k][j] = idx;
					ppp48_idx  [j][i][k] = idx;
					ppp48_idx  [j][k][i] = idx;
					ppp48_idx  [k][i][j] = idx;
					ppp48_idx  [k][j][i] = idx;
					ppp48_sq_x [idx] = (uint8_t) i; 	assert (i < MAX_I);
					ppp48_sq_y [idx] = (uint8_t) j; 	assert (j < MAX_J);
					ppp48_sq_z [idx] = (uint8_t) k; 	assert (k < MAX_K);
					idx++;
				}
			}
		}
	}


	return idx;
}
