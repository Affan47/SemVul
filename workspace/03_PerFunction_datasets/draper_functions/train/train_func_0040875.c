stop()
{
	update();
	running = false;

	switch (mode) {
	case NONE:
	case EXACT:
		break;
	case CONV:
		remaining_time -= elapsed;
		remaining_moves--;
		if (remaining_moves == 0) {
			remaining_time += base_time;
			remaining_moves = base_moves;
		}
		break;
	case INCR:
		remaining_time -= elapsed;
		remaining_time += increment;
		break;
	case SUDDENDEATH:
		remaining_time -= elapsed;
		break;
	}

	return elapsed;
}
