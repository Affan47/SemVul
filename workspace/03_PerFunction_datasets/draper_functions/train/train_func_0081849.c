main (void)
{
	int i;
	for (i = 0; i < 4000; ++i) {
		int a [i];
		int j;

		for (j = 0; j < i; ++j)
			a [j] = i - j - 1;
		compare_sorts (a, i, sizeof (int), compare_ints);
	}

	srandom (time (NULL));
	for (i = 0; i < 2000; ++i) {
		teststruct_t a [200];
		int j;
		for (j = 0; j < 200; ++j) {
			a [j].key = random ();
			a [j].val = random ();
		}

		compare_sorts (a, 200, sizeof (teststruct_t), compare_teststructs);
	}

	return 0;
}
