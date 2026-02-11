ansi_htab(int ig1 _is_unused, int ig2 _is_unused)
{
	int col = cursor_addr % COLS;
	int i;

	held_wrap = False;
	if (col == COLS-1)
		return DATA;
	for (i = col+1; i < COLS-1; i++)
		if (tabs[i/8] & 1<<(i%8))
			break;
	cursor_move(cursor_addr - col + i);
	return DATA;
}
