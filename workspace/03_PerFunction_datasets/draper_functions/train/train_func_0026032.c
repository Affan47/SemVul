board_handicap_stone(struct board *board, int x, int y, FILE *f)
{
	struct move m;
	m.color = S_BLACK; m.coord = coord_xy(board, x, y);

	board_play(board, &m);


	board->moves++;

	char *str = coord2str(m.coord, board);
	if (DEBUGL(1))
		fprintf(stderr, "choosing handicap %s (%d,%d)\n", str, x, y);
	if (f) fprintf(f, "%s ", str);
	free(str);
}
