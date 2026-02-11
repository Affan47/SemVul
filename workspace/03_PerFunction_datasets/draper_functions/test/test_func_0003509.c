g2_PS_bbox_add(g2_PS_device *ps,double x,double y,double size)
	{
	if (ps->bbox == 0)
		{
		ps->x1=x-size;
		ps->x2=x+size;
		ps->y1=y-size;
		ps->y2=y+size;
		ps->bbox=1;
		return;
		}

	if (ps->x1 > x-size)
		ps->x1=x-size;
	else if (ps->x2 < x+size)
		ps->x2=x+size;

	if (ps->y1 > y-size)
		ps->y1=y-size;
	else if (ps->y2 < y+size)
		ps->y2=y+size;
	return;
	}
