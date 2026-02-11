cut_islands(struct cdok_puzzle *puz, int grp,
			const uint8_t *solution)
{
	uint8_t map_copy[CDOK_CELLS];
	struct cdok_group *g = &puz->groups[grp];
	cdok_pos_t start = g->members[0];
	int len = 0;
	int i;

	if (!g->size)
		return;

	memcpy(map_copy, puz->group_map, sizeof(map_copy));
	cdok_flood_fill(map_copy, grp, CDOK_POS_X(start), CDOK_POS_Y(start));

	for (i = 0; i < g->size; i++) {
		cdok_pos_t c = g->members[i];

		if (map_copy[c] != CDOK_GROUP_NONE) {
			puz->values[c] = solution[c];
			puz->group_map[c] = CDOK_GROUP_NONE;
		} else {
			g->members[len++] = c;
		}
	}

	g->size = len;

	if (g->size < 2)
		group_destroy(puz, grp, solution);
}
