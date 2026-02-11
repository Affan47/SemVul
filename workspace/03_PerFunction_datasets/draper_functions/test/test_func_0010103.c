print_board(std::ostream &os, const byte_board_info *board, int indent)
{
	board_iterator	iter;
	iter.init_pos();

	print_indent(os, indent);
	os << "  a b c d e f g h\n";

	int	col = 0, row = 1;
	do {
		if (col == 0) {
			print_indent(os, indent);
			os << row;
		}
		switch (board->board[iter.pos]) {
			case EMPTY:
				os << " .";
				break;
			case BLACK:
				os << " X";
				break;
			case WHITE:
				os << " O";
				break;
			default:
				os << " ?";
		}
		col++;
		if (col == 8) {
			os << '\n';
			col = 0;
			row++;
		}
	} while (iter.next());
}
