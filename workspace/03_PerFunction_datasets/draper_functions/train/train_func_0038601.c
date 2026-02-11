m_bonus(int max, int level)
{
	int bonus, stand, extra, value;


	if (level > MAX_DEPTH - 1) level = MAX_DEPTH - 1;


	bonus = ((max * level) / MAX_DEPTH);


	extra = ((max * level) % MAX_DEPTH);


	if (randint0(MAX_DEPTH) < extra) bonus++;


	stand = (max / 4);


	extra = (max % 4);


	if (randint0(4) < extra) stand++;


	value = Rand_normal(bonus, stand);


	if (value < 0) return (0);


	if (value > max) return (max);


	return (value);
}
