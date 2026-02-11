othello_init (Game *game)
{
	game_getmove = othello_getmove;
	game_getmove_kb = othello_getmove_kb;
	game_who_won = othello_who_won;
	game_eval = othello_eval;
	game_eval_incr = othello_eval_incr;
	game_use_incr_eval = othello_use_incr_eval;
	game_movegen = othello_movegen;
	game_get_rgbmap = othello_get_rgbmap;
	game_white_string = "Red";
	game_black_string = "Blue";
	game_file_label = FILERANK_LABEL_TYPE_ALPHA;
	game_rank_label = FILERANK_LABEL_TYPE_NUM | FILERANK_LABEL_DESC;

	game_doc_about_status = STATUS_COMPLETE;
	if (game == &Othello)
		game_doc_about =
			"Othello\n"
			"Two player game\n"
			"Status: Fully implemented\n"
			"URL: "GAME_DEFAULT_URL ("othello");
	else
		game_doc_about =
			"Othello 6x6\n"
			"Two player game\n"
			"Status: Fully implemented\n"
			"URL: "GAME_DEFAULT_URL ("othello6x6");
	game_doc_rules =
		"Two players take turns in placing balls of either color. The objective is to get as many balls of your color as possible.\n"
		"\n"
		"When you place a ball in such a way that two of your balls sandwich one or more of the opponent's balls along a line (horizontal, vertical, or diagonal), then the sandwiched balls change to your color. You must move in such a way that at least one switch happens.\n"
		"\n"
		"If you don't have a move, you pass by hitting space or clicking on an empty square."
		;
	game_doc_strategy =
		"The number of balls of either color at a given time is, paradoxically, a _very_ poor indicator of who has the advantage. This is because balls can flip color en masse and wildly, especially during the last few moves.\n"
		"\n"
		"Indeed, in the beginning you should try to minimize the number of balls you have. The key is mobility. You must strive to maximize your number of legal moves so that you can try to force your opponent into making bad moves.\n"
		"\n"
		"The corners are key squares, because corner balls never flip. If your opponent blunders into giving you a corner before the final stages of the game, you are practically assured of a win.\n";
}
