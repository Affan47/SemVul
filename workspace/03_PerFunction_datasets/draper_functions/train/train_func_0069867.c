compare(Point * o, PtItem * p, PtItem * q)
{
    double x0;
    double y0;
    double x1;
    double y1;
    double a, b;

    if (q == NULL)
	return -1;
    if ((p->p.x == q->p.x) && (p->p.y == q->p.y))
	return 0;

    x0 = ((double) (p->p.x)) - ((double) (o->x));
    y0 = ((double) (p->p.y)) - ((double) (o->y));
    x1 = ((double) (q->p.x)) - ((double) (o->x));
    y1 = ((double) (q->p.y)) - ((double) (o->y));
    if (x0 >= 0.0) {
	if (x1 < 0.0)
	    return -1;
	else if (x0 > 0.0) {
	    if (x1 > 0.0) {
		a = y1 / x1;
		b = y0 / x0;
		if (b < a)
		    return -1;
		else if (b > a)
		    return 1;
		else if (x0 < x1)
		    return -1;
		else
		    return 1;
	    } else {
		if (y1 > 0.0)
		    return -1;
		else
		    return 1;
	    }
	} else {
	    if (x1 > 0.0) {
		if (y0 <= 0.0)
		    return -1;
		else
		    return 1;
	    } else {
		if (y0 < y1) {
		    if (y1 <= 0.0)
			return 1;
		    else
			return -1;
		} else {
		    if (y0 <= 0.0)
			return -1;
		    else
			return 1;
		}
	    }
	}
    } else {
	if (x1 >= 0.0)
	    return 1;
	else {
	    a = y1 / x1;
	    b = y0 / x0;
	    if (b < a)
		return -1;
	    else if (b > a)
		return 1;
	    else if (x0 > x1)
		return -1;
	    else
		return 1;
	}
    }
}
