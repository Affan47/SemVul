line(const struct point *p, int n, int y)
{
    static int *xs;
    static int max_x;
    int num_x = 0;
    int i;

    for (i = 0; i < n; i++) {
	const struct point *p0 = &p[i];
	const struct point *p1 = &p[i + 1];
	const struct point *tmp;
	double fx, fy;
	long x;

	if (p0->y == p1->y)
	    continue;

	if (p0->y > p1->y)
	    tmp = p0, p0 = p1, p1 = tmp;

	if (p0->y > y)
	    continue;

	if (p1->y <= y)
	    continue;

	fy = y + 0.5;
	fx = (double)p1->x * (fy - p0->y) + (double)p0->x * (p1->y - fy);
	fx /= p1->y - p0->y;
	x = fx < -0x7fffffff ? -0x7fffffff :
	    fx > 0x7fffffff ? 0x7fffffff : (long)floor(fx + 0.5);

	if (num_x >= max_x) {
	    max_x += 20;
	    xs = G_realloc(xs, max_x * sizeof(int));
	}

	xs[num_x++] = x;
    }

    qsort(xs, num_x, sizeof(int), cmp_int);

    for (i = 0; i + 1 < num_x; i += 2)
	fill(xs[i], xs[i + 1], y);
}
