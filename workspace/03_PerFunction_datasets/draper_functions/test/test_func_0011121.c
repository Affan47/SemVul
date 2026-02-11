construct_path(struct line_pnts *Points, double shift, int t)
{
    int i, np, k = 1;
    double *xarray, *yarray, x, y;

    np = Points->n_points;
    xarray = Points->x;
    yarray = Points->y;

    for (i = 0; i < np; i++) {
	x = XCONV(xarray[0] + shift);
	y = YCONV(yarray[0]);
	fprintf(PS.fp, "%.1f %.1f ", x, y);
	if (i == 0 && (t == START_PATH || t == WHOLE_PATH)) {
	    fprintf(PS.fp, "M ");
	}
	else {
	    fprintf(PS.fp, "LN ");
	}
	if (k == 2) {
	    fprintf(PS.fp, "\n");
	    k = 0;
	}
	else {
	    fprintf(PS.fp, " ");
	    k++;
	}
	xarray++;
	yarray++;
    }
    if (t == CLOSE_PATH || t == WHOLE_PATH) {
	fprintf(PS.fp, "CP\n");
    }
    return 1;
}
