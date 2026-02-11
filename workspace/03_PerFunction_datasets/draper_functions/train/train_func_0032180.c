maximize_adjust_offset(FvwmWindow *fw)
{
	int off_x;
	int off_y;
	int dh;
	int dw;

	if (!IS_MAXIMIZED(fw))
	{

		return;
	}
	off_x = fw->g.normal.x - fw->g.max.x - fw->g.max_offset.x;
	off_y = fw->g.normal.y - fw->g.max.y - fw->g.max_offset.y;
	dw = Scr.MyDisplayWidth;
	dh = Scr.MyDisplayHeight;
	if (off_x >= dw)
	{
		fw->g.normal.x -= (off_x / dw) * dw;
	}
	else if (off_x <= -dw)
	{
		fw->g.normal.x += (-off_x / dw) * dw;
	}
	if (off_y >= dh)
	{
		fw->g.normal.y -= (off_y / dh) * dh;
	}
	else if (off_y <= -dh)
	{
		fw->g.normal.y += (-off_y / dh) * dh;
	}

	return;
}
