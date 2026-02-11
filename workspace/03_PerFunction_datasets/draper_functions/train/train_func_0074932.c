is_valid_move(Move mov) const
{
	if (mov.is_null()) {
		return true;
	}

	Square from = mov.from();
	Square to = mov.to();


	if (color_at(from) != get_side() || piece_at(from) != mov.ptype())
		return false;


	if (mov.is_capture()) {
		if (color_at(to) != XSIDE(get_side()))
			return false;
	} else {
		if (color_at(to) != NO_COLOR)
			return false;
	}


#if 0
	switch (piece_at(from)) {
	case PAWN:
		if (mov.flags() & MOVE_CAPTURE
				|| mov.flags() & MOVE_ENPASSANT) {
			if (!pawn_captures(from, color_at(from)).testbit(to))
				return false;
		} else {
			if (!pawn_noncaptures(from, color_at(from)).testbit(to))
				return false;
		}
		break;
	case KNIGHT:
		if (!knight_attacks(from).testbit(to))
			return false;
		break;
	case BISHOP:
		if (!bishop_attacks(from).testbit(to))
			return false;
		break;
	case ROOK:
		if (!rook_attacks(from).testbit(to))
			return false;
		break;
	case QUEEN:
		if (!queen_attacks(from).testbit(to))
			return false;
		break;
	case KING:
		if (!king_attacks(from).testbit(to))
			return false;
		break;
	default:
		BUG("huh?");
	}
#endif


	return true;
}
