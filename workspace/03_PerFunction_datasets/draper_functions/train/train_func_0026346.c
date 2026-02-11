increment_reg(struct Region *region, int wd, int ht,
			 int block_size)
{


    if (region->xmax < wd) {
	region->xmin = region->xmax;
	region->xmax = region->xmin + block_size;
	if (region->xmax > wd)
	    region->xmax = wd;
    }
    else {

	if (region->ymax < ht) {
	    region->xmin = 0;
	    region->xmax = region->xmin + block_size;
	    if (region->xmax > wd)
		region->xmax = wd;

	    region->ymin = region->ymax;
	    region->ymax = region->ymax + block_size;
	    if (region->ymax > ht)
		region->ymax = ht;
	}

	else {
	    return (0);
	}
    }

    if (region->xmin == 0)
	region->free.left = 1;
    else
	region->free.left = 0;

    if (region->ymin == 0)
	region->free.top = 1;
    else
	region->free.top = 0;

    region->free.right = 1;
    region->free.bottom = 1;

    return (1);
}
