scrollability(Window win, int set) {
	double oldest = -1.0;
	int i, index = -1, next_index = -1;
	static int first = 1;

	if (first) {
		for (i=0; i<SCR_RESULTS_MAX; i++) {
			scroll_results[i].win = None;
			scroll_results[i].time = 0.0;
			scroll_results[i].result = 0;
		}
		first = 0;
	}

	if (win == None) {
		return 0;
	}
	if (set == SCR_NONE) {

		for (i=0; i<SCR_RESULTS_MAX; i++) {
			if (win == scroll_results[i].win) {
				return scroll_results[i].result;
			}
			if (scroll_results[i].win == None) {
				break;
			}
		}
		return 0;
	}

	for (i=0; i<SCR_RESULTS_MAX; i++) {
		if (oldest == -1.0 || scroll_results[i].time < oldest) {
			next_index = i;
			oldest = scroll_results[i].time;
		}
		if (win == scroll_results[i].win) {
			index = i;
			break;
		}
		if (next_index >= 0 && scroll_results[i].win == None) {
			break;
		}
	}

	if (set == SCR_SUCCESS) {
		set = 1;
	} else if (set == SCR_FAIL) {
		set = -1;
	} else {
		set = 0;
	}
	if (index == -1) {
		scroll_results[next_index].win = win;
		scroll_results[next_index].time = dnow();
		scroll_results[next_index].result = set;
	} else {
		if (scroll_results[index].result == 1) {


			set = 1;
		} else {
			scroll_results[index].result = set;
		}
		scroll_results[index].time = dnow();
	}

	return set;
}
