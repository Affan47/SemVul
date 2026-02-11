board_symmetry_update(struct board *b, struct board_symmetry *symmetry, coord_t c)
{
	if (likely(symmetry->type == SYM_NONE)) {


		return;
	}

	int x = coord_x(c, b), y = coord_y(c, b), t = board_size(b) / 2;
	int dx = board_size(b) - 1 - x;
	if (DEBUGL(6)) {
		fprintf(stderr, "SYMMETRY [%d,%d,%d,%d|%d=%d] update for %d,%d\n",
			symmetry->x1, symmetry->y1, symmetry->x2, symmetry->y2,
			symmetry->d, symmetry->type, x, y);
	}

	switch (symmetry->type) {
		case SYM_FULL:
			if (x == t && y == t) {

				return;
			}

			if (x == y) {
				symmetry->type = SYM_DIAG_UP;
				symmetry->x1 = symmetry->y1 = 1;
				symmetry->x2 = symmetry->y2 = board_size(b) - 1;
				symmetry->d = 1;
			} else if (dx == y) {
				symmetry->type = SYM_DIAG_DOWN;
				symmetry->x1 = symmetry->y1 = 1;
				symmetry->x2 = symmetry->y2 = board_size(b) - 1;
				symmetry->d = 1;
			} else if (x == t) {
				symmetry->type = SYM_HORIZ;
				symmetry->y1 = 1;
				symmetry->y2 = board_size(b) - 1;
				symmetry->d = 0;
			} else if (y == t) {
				symmetry->type = SYM_VERT;
				symmetry->x1 = 1;
				symmetry->x2 = board_size(b) - 1;
				symmetry->d = 0;
			} else {
break_symmetry:
				symmetry->type = SYM_NONE;
				symmetry->x1 = symmetry->y1 = 1;
				symmetry->x2 = symmetry->y2 = board_size(b) - 1;
				symmetry->d = 0;
			}
			break;
		case SYM_DIAG_UP:
			if (x == y)
				return;
			goto break_symmetry;
		case SYM_DIAG_DOWN:
			if (dx == y)
				return;
			goto break_symmetry;
		case SYM_HORIZ:
			if (x == t)
				return;
			goto break_symmetry;
		case SYM_VERT:
			if (y == t)
				return;
			goto break_symmetry;
		case SYM_NONE:
			assert(0);
			break;
	}

	if (DEBUGL(6)) {
		fprintf(stderr, "NEW SYMMETRY [%d,%d,%d,%d|%d=%d]\n",
			symmetry->x1, symmetry->y1, symmetry->x2, symmetry->y2,
			symmetry->d, symmetry->type);
	}

}
