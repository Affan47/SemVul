check_y_tics (gnuplot_info *gi, const double **Z,
			  FILE *fp)
{
    double ymin, ymax;

    *gi->yfmt = '\0';

    gretl_minmax(gi->t1, gi->t2, Z[gi->list[1]], &ymin, &ymax);
    check_tic_labels(ymin, ymax, gi, 'y');

    if (*gi->yfmt != '\0') {
	fprintf(fp, "set format y \"%s\"\n", gi->yfmt);
    }
}
