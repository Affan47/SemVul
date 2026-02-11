check_time()
{
	if (clock->timeout() && mode == MOVE) {
		stop = true;
	}

	if (showthinking  &&  clock->get_elapsed_time() >= next_update) {
		print_thinking(rootdepth);
	}
}
