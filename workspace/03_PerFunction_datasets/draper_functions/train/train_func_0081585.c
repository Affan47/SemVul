move_mon_to(object *monster, short row, short col)
{
    short c;
    int mrow, mcol;

    mrow = monster->row;
    mcol = monster->col;

    dungeon[mrow][mcol] &= ~MONSTER;
    dungeon[row][col] |= MONSTER;

    c = mvinch_rogue(mrow, mcol);

    if ((c >= 'A') && (c <= 'Z')) {
	if (!detect_monster) {
	    mvaddch_rogue(mrow, mcol, monster->trail_char);
	} else {
	    if (rogue_can_see(mrow, mcol)) {
		mvaddch_rogue(mrow, mcol, monster->trail_char);
	    } else {
		if (monster->trail_char == '.') {
		    monster->trail_char = ' ';
		}
		mvaddch_rogue(mrow, mcol, monster->trail_char);
	    }
	}
    }
    monster->trail_char = mvinch_rogue(row, col);
    if (!blind && (detect_monster || rogue_can_see(row, col))) {
	if ((!(monster->m_flags & INVISIBLE) ||
	     (detect_monster || see_invisible || r_see_invisible))) {
	    mvaddch_rogue(row, col, gmc(monster));
	}
    }
    if ((dungeon[row][col] & DOOR) &&
	(get_room_number(row, col) != cur_room) &&
	(dungeon[mrow][mcol] == FLOOR) && !blind) {
	mvaddch_rogue(mrow, mcol, ' ');
    }
    if (dungeon[row][col] & DOOR) {
	dr_course(monster, ((dungeon[mrow][mcol] & TUNNEL) ? 1 : 0), row, col);
    } else {
	monster->row = row;
	monster->col = col;
    }
}
