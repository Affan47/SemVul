check_tic_labels (double vmin, double vmax,
			     gnuplot_info *gi,
			     char axis)
{
    char s1[32], s2[32];
    int d, err = 0;

    for (d=6; d<12; d++) {
	sprintf(s1, "%.*g", d, vmin);
	sprintf(s2, "%.*g", d, vmax);
	if (strcmp(s1, s2)) {
	    break;
	}
    }

    if (d > 6) {
	if (axis == 'x') {
	    sprintf(gi->xfmt, "%% .%dg", d+1);
	    sprintf(gi->xtics, "%.*g %#.6g", d+1, vmin,
		    (vmax - vmin)/ 4.0);
	} else {
	    sprintf(gi->yfmt, "%% .%dg", d+1);
	}
    }

    return err;
}
