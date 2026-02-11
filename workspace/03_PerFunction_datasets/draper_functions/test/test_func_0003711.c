build_store(int n, int yy, int xx)
{
	int y, x, y0, x0, y1, x1, y2, x2, tmp;


	y0 = yy * 9 + 6;
	x0 = xx * 14 + 12;


	y1 = y0 - randint1((yy == 0) ? 3 : 2);
	y2 = y0 + randint1((yy == 1) ? 3 : 2);
	x1 = x0 - randint1(5);
	x2 = x0 + randint1(5);


	for (y = y1; y <= y2; y++)
	{
		for (x = x1; x <= x2; x++)
		{

			cave_set_feat(y, x, FEAT_PERM_EXTRA);
		}
	}


	tmp = randint0(4);


	if (((tmp == 0) && (yy == 1)) ||
	    ((tmp == 1) && (yy == 0)) ||
	    ((tmp == 2) && (xx == 3)) ||
	    ((tmp == 3) && (xx == 0)))
	{

		tmp = randint0(4);
	}


	switch (tmp)
	{

		case 0:
		{
			y = y2;
			x = rand_range(x1, x2);
			break;
		}


		case 1:
		{
			y = y1;
			x = rand_range(x1, x2);
			break;
		}


		case 2:
		{
			y = rand_range(y1, y2);
			x = x2;
			break;
		}


		default:
		{
			y = rand_range(y1, y2);
			x = x1;
			break;
		}
	}


	cave_set_feat(y, x, FEAT_SHOP_HEAD + n);
}
