eel_irect_contains_point (EelIRect rectangle,
			  int x,
			  int y)
{
	return x >= rectangle.x0
		&& x <= rectangle.x1
		&& y >= rectangle.y0
		&& y <= rectangle.y1;
}
