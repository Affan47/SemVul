findVertical(pointf * pts, double tmin, double tmax,
	     double xcoord, double ymin, double ymax)
{
    pointf Left[4];
    pointf Right[4];
    double t;
    int no_cross = countVertCross(pts, xcoord);

    if (no_cross == 0)
	return -1.0;


    if ((no_cross == 1) && (ROUND(pts[3].x) == ROUND(xcoord))) {
	if ((ymin <= pts[3].y) && (pts[3].y <= ymax)) {
	    return tmax;
	} else
	    return -1.0;
    }


    Bezier(pts, 3, 0.5, Left, Right);
    t = findVertical(Left, tmin, (tmin + tmax) / 2.0, xcoord, ymin, ymax);
    if (t >= 0.0)
	return t;
    return findVertical(Right, (tmin + tmax) / 2.0, tmax, xcoord, ymin,
			ymax);

}
