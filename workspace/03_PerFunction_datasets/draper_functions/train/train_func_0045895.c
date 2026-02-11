inside_thresh(int dx, int dy, int thr) {
	if (thresh_or) {

		if (nabs(dx) <= thresh && nabs(dy) <= thr) {
			return 1;
		}
	} else {

		if (nabs(dx) + nabs(dy) < thr) {
			return 1;
		}
	}
	return 0;
}
