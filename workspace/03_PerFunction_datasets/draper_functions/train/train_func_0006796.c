add(sfmt_t *dest, sfmt_t *src) {
    int dp = dest->idx / 4;
    int sp = src->idx / 4;
    int diff = (sp - dp + SFMT_N) % SFMT_N;
    int p;
    int i;
    for (i = 0; i < SFMT_N - diff; i++) {
	p = i + diff;
	for (int j = 0; j < 4; j++) {
	    dest->state[i].u[j] ^= src->state[p].u[j];
	}
    }
    for (; i < SFMT_N; i++) {
	p = i + diff - SFMT_N;
	for (int j = 0; j < 4; j++) {
	    dest->state[i].u[j] ^= src->state[p].u[j];
	}
    }
}
