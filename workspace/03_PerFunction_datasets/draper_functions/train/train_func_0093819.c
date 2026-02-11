check_limit()
{
	if (mode == NONE || mode == EXACT) {
		return;
	}

	if (limit > hard_limit) {
		limit = hard_limit;
	}


	if ((float) remaining_time / base_time < 0.1f) {
		limit = (int) (limit * 0.8f);
	}


	if ((float) remaining_time / base_time < 0.05f) {
		limit = (int) (limit * 0.8f);
	}


}
