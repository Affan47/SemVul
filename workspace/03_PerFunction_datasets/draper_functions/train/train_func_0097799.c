plD_line_ljii(PLStream *pls, short x1a, short y1a, short x2a, short y2a)
{
    PLDev *dev = (PLDev *) pls->dev;
    int i;
    int xx1 = x1a, yy1 = y1a, xx2 = x2a, yy2 = y2a;
    PLINT x1b, y1b, x2b, y2b;
    PLFLT length, fx, fy, dx, dy;


    yy1 = dev->ymax - (yy1 - dev->ymin);
    yy2 = dev->ymax - (yy2 - dev->ymin);


    plRotPhy(ORIENTATION, dev->xmin, dev->ymin, dev->xmax, dev->ymax, &xx1, &yy1);
    plRotPhy(ORIENTATION, dev->xmin, dev->ymin, dev->xmax, dev->ymax, &xx2, &yy2);

    x1b = xx1, x2b = xx2, y1b = yy1, y2b = yy2;
    length = (PLFLT) sqrt((double)
		     ((x2b - x1b) * (x2b - x1b) + (y2b - y1b) * (y2b - y1b)));

    if (length == 0.)
	length = 1.;
    dx = (xx2 - xx1) / length;
    dy = (yy2 - yy1) / length;

    fx = xx1;
    fy = yy1;
    setpoint((PLINT) xx1, (PLINT) yy1);
    setpoint((PLINT) xx2, (PLINT) yy2);

    for (i = 1; i <= (int) length; i++)
	setpoint((PLINT) (fx += dx), (PLINT) (fy += dy));
}
