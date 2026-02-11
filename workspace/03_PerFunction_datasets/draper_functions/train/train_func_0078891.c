sk_setpoints(struct s_skier *s)
{
	double unit, points = 60;
	double lowest = 100, bigest = -2;
	int k = K/2, i;

	if (s->state == CRASH)
		for (i = 0; i < 5; i++)
			s->judge[i] = -7;


	if (k >= 150) {
		unit = 1.2;
		points = 120;
	} else if (k >= 100)
		unit = 1.8;
	else if (k >= 50)
		unit = 2;
	else
		unit = 2.1;

	if (s->alight > k)
		for (; k <= s->alight; k++)
			points += unit;
	else if (s->alight < k)
		for (; k >= s->alight; k--)
			points -= unit;

	for (i = 0; i < 5; i++) {
		if (s->alight < K/2)
			s->judge[i] -= 3;
		if (s->bend == 3)
			s->judge[i] -= 1;
		s->judge[i] += 20;
		s->judge[i] -= d(s->bend)/d(2);
		if (d(2)-1)
			s->judge[i] -= 0.5;
		if (lowest > s->judge[i])
			lowest = s->judge[i];
		if (bigest < s->judge[i])
			bigest = s->judge[i];
	}

	for (i =0; i < 5; i++) {
		if (s->judge[i] == bigest)
			bigest = -1;
		else if (s->judge[i] == lowest)
			lowest = -1;
		else
			points += s->judge[i];
	}

	s->points += points;
	s->last_points = points;

	if (s->hill->record < s->alight && s->state != CRASH) {
		s->hill->record = s->alight;
		xfree(s->hill->owner);
		s->hill->owner = strdup(s->name);
		s->new_owner = 1;
		hl_record_write(s->hill);
	}
}
