thin_ring_stats(struct ccd_frame *fr, int x, int y,
		int r2, struct rstats *rs, double min, double max)
{
	int ix, iy;
	int xs, ys;
	int xe, ye;
	int xc, yc;
	int w;
	int nring = 0, nskipped = 0;
	float v;
	double sum, sumsq, r;
	int dy2, rsq1, rsq2;
	double ring[RING_MAX];
	int all;


	xc = x;
	yc = y;


	xs = (xc-r2);
	xe = (xc+r2+1);
	ys = (yc-r2);
	ye = (yc+r2+1);
	w = fr->w;

	if (xs < 0)
		xs = 0;
	if (ys < 0)
		ys = 0;
	if (xe >= w)
		xe = w - 1;
	if (ye >= fr->h)
		ye = fr->h - 1;

	all = fr->h * fr->w;


	sum=0.0;
	sumsq = 0.0;
	rs->min = HUGE;
	rs->max = -HUGE;
	rsq1 = sqr(r2);
	rsq2 = sqr(r2+1.001);
	for (iy = ys; iy < ye; iy++) {
		dy2 = (iy - yc) * (iy - yc);
		for (ix = xs; ix < xe; ix++) {
			v = get_pixel_luminence(fr, ix, iy);
			if (((r = (ix - xc) * (ix - xc) + dy2))
			    < rsq1 || r > rsq2)
				continue;
			if (v < min || v > max) {
				nskipped ++;
				continue;
			}
			if (nring < RING_MAX)
				ring[nring++] = v;
			sum += v;
			sumsq += v*v;
			if (v < rs->min)
				rs->min = v;
			if (v > rs->max) {
				rs->max = v;
				rs->max_x = ix;
				rs->max_y = iy;
			}
		}
	}


	rs->all = nring + nskipped;
	rs->used = nring;
	rs->sum = sum;
	rs->avg = sum / rs->used;
	rs->sigma = sqrt(sumsq / rs->used - sqr(sum / rs->used));
	rs->median = dmedian(ring, nring);


	return 0;
}
