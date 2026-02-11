next()
{
	const Board & board = tree->get_board();
	Move mov;

	switch (state) {
	case GEN_CAPTURES:
		ASSERT_DEBUG(!captures_generated);
		ASSERT_DEBUG(movelist.size() == 0);
		board.generate_captures(&movelist, false);
		captures_generated = true;


	case SCORE_CAPTURES:
		ASSERT_DEBUG(captures_generated);
		score_moves();
		state = CAPTURES;

	case CAPTURES:
		ASSERT_DEBUG(captures_generated);
		mov = pick();
		if (mov) {
			return mov;
		}
		if (type == QUIESCE) {
			state = DONE;
			break;
		}


	case GEN_NONCAPTURES:
		ASSERT_DEBUG(captures_generated);
		ASSERT_DEBUG(!noncaptures_generated);
		board.generate_noncaptures(&movelist);
		noncaptures_generated = true;


	case SCORE_NONCAPTURES:
		ASSERT_DEBUG(noncaptures_generated);
		score_moves();
		state = NONCAPTURES;

	case NONCAPTURES:
		ASSERT_DEBUG(noncaptures_generated);
		mov = pick();
		if (mov) {
			return mov;
		}
		state = DONE;
		break;

	case GEN_ESCAPES:
		ASSERT_DEBUG(in_check());
		ASSERT_DEBUG(!escapes_generated);
		ASSERT_DEBUG(movelist.size() == 0);

		board.generate_moves(&movelist, false);
		escapes_generated = true;


	case SCORE_ESCAPES:
		ASSERT_DEBUG(escapes_generated);
		score_moves();
		state = ESCAPES;

	case ESCAPES:
		ASSERT_DEBUG(escapes_generated);
		mov = pick();
		if (mov) {
			return mov;
		}
		state = DONE;
		break;

	case SCORE_ALL:
		score_moves();
		state = ALL;

	case ALL:
		mov = pick();
		if (mov) {
			return mov;
		}
		state = DONE;
		break;

	default:
		BUG("node status is bad: %d", state);
	}

	return NO_MOVE;
}
