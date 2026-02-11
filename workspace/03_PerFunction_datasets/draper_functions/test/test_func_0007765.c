COM_Box_abs(int x1, int y1, int x2, int y2)
{
    int x[4], y[4];

    if (driver->Box_abs) {
	(*driver->Box_abs) (x1, y1, x2, y2);
	return;
    }

    x[0] = x1;
    y[0] = y1;
    x[1] = x1;
    y[1] = y2;
    x[2] = x2;
    y[2] = y2;
    x[3] = x2;
    y[3] = y1;

    COM_Polygon_abs(x, y, 4);
}
