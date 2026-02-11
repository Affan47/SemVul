move_cursor(u16 x, u16 y)
{
	if (x>=width) x = width-1;
	if (y>=height) y = height-1;
	cursor_x = x;
	cursor_y = y;
}
