san(const Board & board, int nonstd) const
{
	(void) nonstd;

	char ss[12];

	const char * check = "";
	Board b = board;
	b.make_move(*this);
	if (b.is_mate() || b.is_stalemate()) {
		check = "#";
	} else if (b.in_check()) {
		check = "+";
	}

	snprintf(ss, sizeof(ss), "%c%s%s%s%s",
			piece_char[board.piece_at(from())],
			square_str[from()],
			is_capture() ? "x" : "-",
			square_str[to()],
			check);

	return std::string(ss);
}
