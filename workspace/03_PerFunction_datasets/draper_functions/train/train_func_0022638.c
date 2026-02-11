get_beat(struct meter_s *m)
{
	int top, bot;

	if (m->meter[0].top[0] == 'C') {
		if (m->meter[0].top[0] == '|')
			return BASE_LEN / 2;
		return BASE_LEN / 4;
	}
	if (m->meter[0].bot[0] == '\0')
		return BASE_LEN / 4;
	sscanf(m->meter[0].top, "%d", &top);
	sscanf(m->meter[0].bot, "%d", &bot);
	if (bot >= 8 && top >= 6 && top % 3 == 0)
		return BASE_LEN * 3 / 8;
	return BASE_LEN / bot;
}
