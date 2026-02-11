transpose_vector(unsigned long ncols, uint64_t *v, uint64_t **trans) {


	unsigned long i, j;
	unsigned long col;
	uint64_t mask, word;

	for (i = 0; i < ncols; i++) {
		col = i / 64;
		mask = bitmask[i % 64];
		word = v[i];
		j = 0;
		while (word) {
			if (word & 1)
				trans[j][col] |= mask;
			word = word >> 1;
			j++;
		}
	}
}
