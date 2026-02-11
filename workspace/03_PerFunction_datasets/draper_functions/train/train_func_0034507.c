randcalc(random_value v, int level, aspect rand_aspect) {
	if (rand_aspect == EXTREMIFY) {
		int min = randcalc(v, level, MINIMISE);
		int max = randcalc(v, level, MAXIMISE);
		return abs(min) > abs(max) ? min : max;

	} else {
		int dmg   = damcalc(v.dice, v.sides, rand_aspect);
		int bonus = m_bonus_calc(v.m_bonus, level, rand_aspect);
		return v.base + dmg + bonus;
	}
}
