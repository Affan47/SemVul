getCubicBezierBBox(double x0, double y0, double x1, double y1, double x2, double y2, double x, double y,
                        double &xmin, double &ymin, double &xmax, double &ymax)
{
	xmin = x0 < x ? x0 : x;
	xmax = x0 > x ? x0 : x;
	ymin = y0 < y ? y0 : y;
	ymax = y0 > y ? y0 : y;

	for (double t = 0.0; t <= 1.0; t+=0.01)
	{
		double tmpx = cubicBase(t, x0, x1, x2, x);
		xmin = tmpx < xmin ? tmpx : xmin;
		xmax = tmpx > xmax ? tmpx : xmax;
		double tmpy = cubicBase(t, y0, y1, y2, y);
		ymin = tmpy < ymin ? tmpy : ymin;
		ymax = tmpy > ymax ? tmpy : ymax;
	}
}

}
