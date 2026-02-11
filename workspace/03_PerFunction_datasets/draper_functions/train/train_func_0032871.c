FindBefore(int x, int lower, int upper) const {
	do {
		int middle = (upper + lower + 1) / 2;
		int posMiddle = positions[middle];
		if (x < posMiddle) {
			upper = middle - 1;
		} else {
			lower = middle;
		}
	} while (lower < upper);
	return lower;
}
