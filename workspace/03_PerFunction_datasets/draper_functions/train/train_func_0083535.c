get_prompt()
{
	const char * a1 = ansicolor ? "\033[1m" : "";
	const char * a2 = ansicolor ? "\033[0m" : "";

	if (game->is_over()) {
		return strprintf("%s(game over):%s ", a1, a2);
	}

	std::string s = a1;

	if (flag_analyze) {
		s += "(analyze mode) ";
	} else if (flag_ponder && !flag_force && game->is_running()) {
		s += "(pondering) ";
	}

	s += strprintf("%s (%d): ",
			game->get_board().get_side() == WHITE
					? "White" : "Black",
			game->get_board().get_moveno());

	s += a2;

	if (flag_analyze || (flag_ponder && flag_showthinking)) {
		s += "\n";
	}

	return s;
}
