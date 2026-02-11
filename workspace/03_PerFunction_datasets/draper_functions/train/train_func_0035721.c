init_aaidx (void)

{
	index_t idx;
	SQUARE x, y;


	for (x = 0; x < 64; x++) {
		for (y = 0; y < 64; y++) {
			IDX_set_empty(aaidx [x][y]);
		}
	}

	for (idx = 0; idx < MAX_AAINDEX; idx++)
		aabase [idx] = 0;

	idx = 0;
	for (x = 0; x < 64; x++) {
		for (y = x + 1; y < 64; y++) {

			assert (idx == (int)((y - x) + x * (127-x)/2 - 1) );

			if (IDX_is_empty(aaidx [x][y])) {
				aaidx [x] [y] = idx;
				aaidx [y] [x] = idx;
				aabase [idx] = (unsigned char) x;
				idx++;
			} else {
				assert (aaidx [x] [y] == idx);
				assert (aabase [idx] == x);
			}


		}
	}

	assert (idx == MAX_AAINDEX);

	return idx;
}
