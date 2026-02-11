main(const char * filename)
{
	source_t mainsource;
	if (filename != NULL) {
		mainsource.name = filename;
		mainsource.line = 0;
		mainsource.fp = fopen(filename, "r");
		if (mainsource.fp == NULL) {
			fprintf(stderr, "Cannot open %s for reading: %s\n",
					filename, strerror(errno));
			exit(EXIT_FAILURE);
		}
	} else {
		mainsource.name = "(stdin)";
		mainsource.line = 0;
		mainsource.fp = stdin;
	}
	if (sources.size() != 0) {
		sources.pop_front();
		sources.push_front(mainsource);
	} else {
		source = mainsource;
	}

	cmd_new();

	if (!xboard && source.fp == stdin) {
		printf("\nType \"help\" for a list of available commands.\n\n");
	}

	quit = false;
	while (!quit) {
		stop = false;

		if (game->is_over()) {

		} else if (flag_playboth) {

			myside = game->get_side();
			engine_move();
			continue;
		} else if (!flag_force && game->get_side() == myside) {

			engine_move();
			continue;
		} else if (flag_ponder && !flag_force && game->is_running()) {

			DBG(1, "starting background search...");
			search->start_thread(*game, Search::PONDER, myside);
		} else if (flag_analyze) {

			DBG(1, "starting background search...");
			search->start_thread(*game, Search::ANALYZE, NO_COLOR);
		}

		input();
	}

	search->stop_thread();
}
