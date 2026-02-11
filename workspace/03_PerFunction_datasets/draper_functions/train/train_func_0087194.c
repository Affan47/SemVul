add_mazes(void)
{
    short i, j;
    short start;
    short maze_percent;

    if (cur_level > 1) {
	start = get_rand(0, (MAXROOMS - 1));
	maze_percent = (cur_level * 5) / 4;

	if (cur_level > 15) {
	    maze_percent += cur_level;
	}
	for (i = 0; i < MAXROOMS; i++) {
	    j = ((start + i) % MAXROOMS);
	    if (rooms[j].is_room & R_NOTHING) {
		if (rand_percent(maze_percent)) {
		    rooms[j].is_room = R_MAZE;
		    make_maze(get_rand
			      (rooms[j].top_row + 1, rooms[j].bottom_row - 1),
			      get_rand(rooms[j].left_col + 1,
				       rooms[j].right_col - 1),
			      rooms[j].top_row, rooms[j].bottom_row,
			      rooms[j].left_col, rooms[j].right_col);
		    hide_boxed_passage(rooms[j].top_row, rooms[j].left_col,
				       rooms[j].bottom_row, rooms[j].right_col,
				       get_rand(0, 2));
		}
	    }
	}
    }
}
