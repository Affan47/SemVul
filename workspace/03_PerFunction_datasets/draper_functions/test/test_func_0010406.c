ck_barrier_dissemination(struct ck_barrier_dissemination *barrier,
    struct ck_barrier_dissemination_state *state)
{
	unsigned int i;
	unsigned int size = barrier->size;

	for (i = 0; i < size; ++i) {
		unsigned int *pflag, *tflag;

		pflag = barrier[state->tid].flags[state->parity][i].pflag;
		tflag = &barrier[state->tid].flags[state->parity][i].tflag;


		ck_pr_store_uint(pflag, state->sense);


		while (ck_pr_load_uint(tflag) != state->sense)
			ck_pr_stall();
	}


	if (state->parity == 1)
		state->sense = ~state->sense;

	state->parity = 1 - state->parity;

	ck_pr_fence_acquire();
	return;
}
