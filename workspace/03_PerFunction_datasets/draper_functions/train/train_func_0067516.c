Rand_state_init(u32b seed) {
	int i, j;


	STATE[0] = seed;


	for (i = 1; i < RAND_DEG; i++)
		STATE[i] = LCRNG(STATE[i - 1]);


	for (i = 0; i < RAND_DEG * 10; i++) {

		j = (state_i + 1) % RAND_DEG;


		STATE[j] += STATE[state_i];


		state_i = j;
	}
}
