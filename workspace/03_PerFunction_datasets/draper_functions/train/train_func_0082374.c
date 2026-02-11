print(FILE * fp, Move last_move) const
{
	Square sq;
	char c;

	for (int i=9; i>=0; i--) {
		fprintf(fp, "%d ", i);
		for (int j=0; j<=8; j++) {
			sq = SQUARE(i,j);
			if (piece_at(sq) != NO_PIECE) {
				ASSERT(color_at(sq) != NO_COLOR);
				c = piece_char[piece_at(sq)];
				c = (color_at(sq) == WHITE)
					? toupper(c) : tolower(c);
			} else {
				c = '+';
			}

			if (j != 0) {
				fprintf(fp, "---");
			}

			if (ansicolor && fp == stdout) {
				const char * a2 = "";
				const char * a3 = "";
				if (last_move && (sq == last_move.from()
						|| sq == last_move.to())) {
					a2 = XSIDE(side) == WHITE
						? "\033[31;1m"
						: "\033[34;1m";
					a3 = "\033[7m";
				} else {
					if (color_at(sq) == WHITE) {
						a2 = "\033[31;1m";
					} else if (color_at(sq) == BLACK) {
						a2 = "\033[34;1m";
					}
				}

				const char * a4 = "\033[0m";
				fprintf(fp, "%s%s%c%s", a2, a3, c, a4);
			} else {
				fprintf(fp, "%c", c);
			}
		}

		fprintf(fp, "\n");

		if (i == 9 || i == 2) {
			fprintf(fp, "  |   |   |   | \\ | / |   |   |   |\n");
		} else if (i == 8 || i == 1) {
			fprintf(fp, "  |   |   |   | / | \\ |   |   |   |\n");
		} else if (i == 5) {
			fprintf(fp, "  |                               |\n");
		} else if (i != 0) {
			fprintf(fp, "  |   |   |   |   |   |   |   |   |\n");
		}

	}
	fprintf(fp, "\n");
	fprintf(fp, "  A   B   C   D   E   F   G   H   I\n");

	fprintf(fp, "\n  [%d] %s\n",
			moveno,
			(side == WHITE) ? "White" : "Black");

	if (last_move) {
		fprintf(fp, "  Last move by %s: %s\n",
			(side == WHITE) ? "Black" : "White",
			last_move.str().c_str());
	}
}
