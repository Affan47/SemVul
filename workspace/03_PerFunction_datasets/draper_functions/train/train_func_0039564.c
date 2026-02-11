msg_ceol()
{
	if (!msg_check_screen())
		return;
	screen_fill(msg_row, msg_row + 1, msg_col, (int)Columns, ' ', ' ');
	screen_fill(msg_row + 1, (int)Rows, 0, (int)Columns, ' ', ' ');
}
