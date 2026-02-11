rnd(int low, int high) {
	int i;
	float randomperc();

	if (low >= high)
		i = low;
	else {
		i = (randomperc() * (high - low + 1)) + low;
		if (i > high)
			i = high;
	}

	return (i);
}
