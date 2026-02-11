fill_it(int rn, boolean do_rec_de)
{
    short i;
    short tunnel_dir, door_dir, drow, dcol;
    short target_room, rooms_found = 0;
    short srow, scol, t;
    static short offsets[4] = { -1, 1, 3, -3 };
    boolean did_this = 0;

    for (i = 0; i < 10; i++) {
	srow = get_rand(0, 3);
	scol = get_rand(0, 3);
	t = offsets[srow];
	offsets[srow] = offsets[scol];
	offsets[scol] = t;
    }
    for (i = 0; i < 4; i++) {

	target_room = rn + offsets[i];

	if (((target_room < 0) || (target_room >= MAXROOMS)) ||
	    (!(same_row(rn, target_room) || same_col(rn, target_room))) ||
	    (!(rooms[target_room].is_room & (R_ROOM | R_MAZE)))) {
	    continue;
	}
	if (same_row(rn, target_room)) {
	    tunnel_dir = (rooms[rn].left_col < rooms[target_room].left_col) ?
		RIGHT : LEFT;
	} else {
	    tunnel_dir = (rooms[rn].top_row < rooms[target_room].top_row) ?
		DOWN : UPWARD;
	}
	door_dir = ((tunnel_dir + 4) % DIRS);
	if (rooms[target_room].doors[door_dir / 2].oth_room != NO_ROOM) {
	    continue;
	}
	if (((!do_rec_de) || did_this) ||
	    (!mask_room(rn, &srow, &scol, TUNNEL))) {
	    srow = (rooms[rn].top_row + rooms[rn].bottom_row) / 2;
	    scol = (rooms[rn].left_col + rooms[rn].right_col) / 2;
	}
	put_door(&rooms[target_room], door_dir, &drow, &dcol);
	rooms_found++;
	draw_simple_passage(srow, scol, drow, dcol, tunnel_dir);
	rooms[rn].is_room = R_DEADEND;
	dungeon[srow][scol] = TUNNEL;

	if ((i < 3) && (!did_this)) {
	    did_this = 1;
	    if (coin_toss()) {
		continue;
	    }
	}
	if ((rooms_found < 2) && do_rec_de) {
	    recursive_deadend(rn, offsets, srow, scol);
	}
	break;
    }
}
