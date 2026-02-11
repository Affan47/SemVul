compute_color (gdImagePtr oim, gdImagePtr nim, my_cquantize_ptr cquantize,
	       boxptr boxp, int icolor)
{
	hist3d histogram = cquantize->histogram;
	histptr histp;
	int c0, c1, c2;
	int c0min, c0max, c1min, c1max, c2min, c2max;
	long count = 0;
	long total = 0;
	long c0total = 0;
	long c1total = 0;
	long c2total = 0;
	(void)oim;

	c0min = boxp->c0min;
	c0max = boxp->c0max;
	c1min = boxp->c1min;
	c1max = boxp->c1max;
	c2min = boxp->c2min;
	c2max = boxp->c2max;

	for (c0 = c0min; c0 <= c0max; c0++)
		for (c1 = c1min; c1 <= c1max; c1++) {
			histp = &histogram[c0][c1][c2min];
			for (c2 = c2min; c2 <= c2max; c2++) {
				if ((count = *histp++) != 0) {
					total += count;
					c0total +=
					    ((c0 << C0_SHIFT) + ((1 << C0_SHIFT) >> 1)) * count;
					c1total +=
					    ((c1 << C1_SHIFT) + ((1 << C1_SHIFT) >> 1)) * count;
					c2total +=
					    ((c2 << C2_SHIFT) + ((1 << C2_SHIFT) >> 1)) * count;
				}
			}
		}


	if (count) {
		nim->red[icolor] = (int) ((c0total + (total >> 1)) / total);
		nim->green[icolor] = (int) ((c1total + (total >> 1)) / total);
		nim->blue[icolor] = (int) ((c2total + (total >> 1)) / total);
	} else {
		nim->red[icolor] = 255;
		nim->green[icolor] = 255;
		nim->blue[icolor] = 255;
	}
	nim->open[icolor] = 0;
}
