miner_handle_next (void)
{
	if (finished_miners) {
		return;
	}

	if (!current_miner) {
		current_miner = miners;
	} else {
		current_miner = current_miner->next;
	}

	if (!current_miner) {
		finished_miners = TRUE;

		g_message ("All miners are now finished");


		if (no_daemon && main_loop) {
			g_main_loop_quit (main_loop);
		}

		return;
	}


	if (miner_disabled_check ()) {
		return;
	}

	if (!tracker_miner_is_started (current_miner->data)) {
		g_message ("Starting next miner...");
		tracker_miner_start (current_miner->data);
	}
}
