FindScreenOfXY(int x, int y)
{
	int i;

	x = x % screens_xi[0].width;
	while (x < 0)
	{
		x += screens_xi[0].width;
	}
	y = y % screens_xi[0].height;
	while (y < 0)
	{
		y += screens_xi[0].height;
	}
	for (i = first_to_check;  i <= last_to_check;  i++)
	{
		if (x >= screens[i].x_org  &&
		    x < screens[i].x_org + screens[i].width  &&
		    y >= screens[i].y_org  &&
		    y < screens[i].y_org + screens[i].height)
		{
			return i;
		}
	}


	return 0;
}
