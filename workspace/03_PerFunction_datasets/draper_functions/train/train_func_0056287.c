normalize_labels(struct cdok_puzzle *puz)
{
	int i;

	for (i = 0; i < CDOK_GROUPS; i++) {
		struct cdok_group *g = &puz->groups[i];
		int min = 0;
		int j;

		if (!g->size)
			continue;

		for (j = 1; j < g->size; j++)
			if (g->members[j] < g->members[min])
				min = j;

		j = g->members[min];
		g->members[min] = g->members[0];
		g->members[0] = j;
	}
}
