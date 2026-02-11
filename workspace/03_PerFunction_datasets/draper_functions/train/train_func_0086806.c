arizona_find_fratio(unsigned int Fref, int *fratio)
{
	int i;


	for (i = 0; i < ARRAY_SIZE(fll_fratios); i++) {
		if (fll_fratios[i].min <= Fref && Fref <= fll_fratios[i].max) {
			if (fratio)
				*fratio = fll_fratios[i].fratio;
			return fll_fratios[i].ratio;
		}
	}

	return -EINVAL;
}
