shift_ll(LIKELIHOOD **** ll_pym,
		    struct Region *region, int block_size)
{
    static int first = 1;
    static int xoffset[20];
    static int yoffset[20];

    int xdelta;
    int ystart, ystop, ydelta;
    int D;
    int k, i;
    int block_size_k;
    struct Region region_buff;


    if (first) {
	D = levels(block_size, block_size);
	for (k = 0; k <= D; k++)
	    xoffset[k] = yoffset[k] = 0;
	first = 0;
    }


    copy_reg(region, &region_buff);


    D = levels(block_size, block_size);
    block_size_k = block_size;
    for (k = 0; k <= D; k++) {
	xdelta = region->xmin - xoffset[k];
	ydelta = region->ymin - yoffset[k];
	xoffset[k] = region->xmin;
	yoffset[k] = region->ymin;

	ystart = region->ymin;
	ystop = ystart + block_size_k;

	ll_pym[k] -= ydelta;
	for (i = ystart; i < ystop; i++)
	    ll_pym[k][i] -= xdelta;
	dec_reg(region);
	block_size_k = block_size_k / 2;
    }


    copy_reg(&region_buff, region);

    return 0;
}
