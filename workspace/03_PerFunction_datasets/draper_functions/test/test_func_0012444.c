collect_discards(void)
{
    int row, col, cardno = 0, finish, gridno;

    for (row = HEARTS; row <= CLUBS; row++) {
	finish = 0;
	for (col = 1; col < GRID_WIDTH; col++) {
	    gridno = row * GRID_WIDTH + col;

	    if ((grid[gridno] != (grid[gridno - 1] + 1)) && (finish == 0)) {
		finish = 1;
		freeptr[row] = gridno;
	    };

	    if ((finish != 0) && (grid[gridno] != NOCARD))
		deck[cardno++] = grid[gridno];
	}
    }
    return cardno;
}
