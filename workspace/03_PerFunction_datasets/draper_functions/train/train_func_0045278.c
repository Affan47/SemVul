format_clue(char *text, int max_len,
		       const struct cdok_puzzle *puz,
		       cdok_pos_t c)
{
	const struct cdok_group *g;

	if (puz->group_map[c] == CDOK_GROUP_NONE) {
		text[0] = 0;
		return 0;
	}

	g = &puz->groups[puz->group_map[c]];
	if (g->members[0] == c)
		return snprintf(text, max_len, "%d%c", g->target, g->type);

	text[0] = 0;
	return 0;
}
