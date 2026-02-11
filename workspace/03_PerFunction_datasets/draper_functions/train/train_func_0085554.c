run_clip(int ncols, int nrows, int u_w, int u_l, int left, int top,
	      CELL ** units, int id, float radius)
{
    int i, j;
    double center_row, center_col;
    double dist;

    G_sleep_on_error(0);


    if (ncols < left + u_w || nrows < top + u_l) {
	fprintf(stderr, "\n");
	fprintf(stderr,
		"   ******************************************************\n");
	fprintf(stderr,
		"    Sampling units do not fit within the current region. \n");
	fprintf(stderr,
		"    Either correct the region or redo the sampling unit  \n");
	fprintf(stderr,
		"    selection using r.le.setup.  This error message came \n");
	fprintf(stderr,
		"    from an analysis of the r.le.para/units file and the \n");
	fprintf(stderr,
		"    current region setting.                              \n");
	fprintf(stderr,
		"   ******************************************************\n");
	exit(EXIT_FAILURE);
    }

    if (choice->units) {
	if (radius) {
	    center_row = ((double)(top + 1) + ((double)u_l - 1) / 2);
	    center_col = ((double)(left + 1) + ((double)u_w - 1) / 2);

	    for (i = top + 1; i < top + 1 + u_l; i++) {
		for (j = left + 1; j < left + 1 + u_w; j++) {
		    dist =
			sqrt(((double)i - center_row) * ((double)i -
							 center_row) +
			     ((double)j - center_col) * ((double)j -
							 center_col));
		    if (dist < radius)
			*(*(units + i) + j) = id + 1;
		}
	    }
	}
	else {
	    for (i = top + 1; i < top + 1 + u_l; i++) {
		for (j = left + 1; j < left + 1 + u_w; j++)
		    *(*(units + i) + j) = id + 1;
	    }
	}
    }

    cell_clip_drv(left, top, u_w, u_l, NULL, 0, radius);

    return;
}
