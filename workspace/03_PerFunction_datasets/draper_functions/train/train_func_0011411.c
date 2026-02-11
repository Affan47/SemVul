darken_room(short rn)
{
    short i, j;

    for (i = rooms[rn].top_row + 1; i < rooms[rn].bottom_row; i++) {
	for (j = rooms[rn].left_col + 1; j < rooms[rn].right_col; j++) {
	    if (blind) {
		mvaddch_rogue(i, j, ' ');
	    } else {
		if (!(dungeon[i][j] & (OBJECT | STAIRS)) &&
		    !(detect_monster && (dungeon[i][j] & MONSTER))) {
		    if (!imitating(i, j)) {
			mvaddch_rogue(i, j, ' ');
		    }
		    if ((dungeon[i][j] & TRAP) && (!(dungeon[i][j] & HIDDEN))) {
			mvaddch_rogue(i, j, '^');
		    }
		}
	    }
	}
    }
}
