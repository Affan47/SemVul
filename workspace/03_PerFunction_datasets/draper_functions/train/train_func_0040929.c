board_estimated_moves_left(struct board *b)
{
	int total_points = (board_size(b)-2)*(board_size(b)-2);
	int moves_left = (b->flen - total_points*EXPECTED_FINAL_EMPTY_PERCENT/100)/2;
	return moves_left > MIN_MOVES_LEFT ? moves_left : MIN_MOVES_LEFT;
}
