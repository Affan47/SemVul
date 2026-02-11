fill_inverse_cmap (
    gdImagePtr oim, gdImagePtr nim, my_cquantize_ptr cquantize,
    int c0, int c1, int c2)


{
	hist3d histogram = cquantize->histogram;
	int minc0, minc1, minc2;
	int ic0, ic1, ic2;
	register JSAMPLE *cptr;
	register histptr cachep;

	JSAMPLE colorlist[MAXNUMCOLORS];
	int numcolors;

	JSAMPLE bestcolor[BOX_C0_ELEMS * BOX_C1_ELEMS * BOX_C2_ELEMS];


	c0 >>= BOX_C0_LOG;
	c1 >>= BOX_C1_LOG;
	c2 >>= BOX_C2_LOG;


	minc0 = (c0 << BOX_C0_SHIFT) + ((1 << C0_SHIFT) >> 1);
	minc1 = (c1 << BOX_C1_SHIFT) + ((1 << C1_SHIFT) >> 1);
	minc2 = (c2 << BOX_C2_SHIFT) + ((1 << C2_SHIFT) >> 1);


	numcolors =
	    find_nearby_colors (oim, nim, cquantize, minc0, minc1, minc2, colorlist);
	find_best_colors (oim, nim, cquantize, minc0, minc1, minc2, numcolors,
			  colorlist, bestcolor);


	c0 <<= BOX_C0_LOG;
	c1 <<= BOX_C1_LOG;
	c2 <<= BOX_C2_LOG;
	cptr = bestcolor;
	for (ic0 = 0; ic0 < BOX_C0_ELEMS; ic0++) {
		for (ic1 = 0; ic1 < BOX_C1_ELEMS; ic1++) {
			cachep = &histogram[c0 + ic0][c1 + ic1][c2];
			for (ic2 = 0; ic2 < BOX_C2_ELEMS; ic2++) {
				*cachep++ = (histcell) ((*cptr++) + 1);
			}
		}
	}
}
