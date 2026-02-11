advance_random() {
	int j1;
	double new_random;

	for (j1 = 0; j1 < 24; j1++) {
		new_random = oldrand[j1] - oldrand[j1 + 31];
		if (new_random < 0.0)
			new_random = new_random + 1.0;
		oldrand[j1] = new_random;
	}

	for (j1 = 24; j1 < 55; j1++) {
		new_random = oldrand[j1] - oldrand[j1 - 24];
		if (new_random < 0.0)
			new_random = new_random + 1.0;
		oldrand[j1] = new_random;
	}

}
