segment_intersect(struct Line *line, struct Point *p, double *y)
{
    struct Point *p1 = line->p1;
    struct Point *p2 = line->p2;
    double t;

    if (in_between(p, line)) {
	if (p2->x != p1->x) {
	    t = (p->x - p1->x) / (p2->x - p1->x);

	    *y = p1->y + t * (p2->y - p1->y);
	}
	else {
	    if (p1->y > p->y || p2->y > p->y)
		return -1;

	    *y = p1->y > p2->y ? p1->y : p2->y;
	}

	return 1;
    }
    else
	return -1;

}
