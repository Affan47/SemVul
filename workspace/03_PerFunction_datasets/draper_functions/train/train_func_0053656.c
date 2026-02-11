recursive_delete (byte *board, int x, int y, int val)
{
	if (x < 0 || y < 0 || x >= board_wid || y >= board_heit)
		return;
	if (board[y * board_wid + x] != val)
		return;
	board[y * board_wid + x] = 0;
	recursive_delete (board, x - 1, y   , val);
	recursive_delete (board, x + 1, y   , val);
	recursive_delete (board, x    , y - 1, val);
	recursive_delete (board, x    , y + 1, val);
}
