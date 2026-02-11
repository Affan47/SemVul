board_score(search_info &info, int player)
		{
			pthread_testcancel();
			if (info.board->board_black_score() == 0
			    || info.board->board_white_score() == 0)
				return end_board_score(info);
			return pattern_eval(info.board)
			       + parity_eval_alpha_beta(info, player);
		}
