print_plotbars (plotbars *bars, FILE *fp)
{
    double y0 = bars->ymin;
    double y1 = bars->ymax;
    int i, started, stopped;

    for (i=0; i<bars->n; i++) {
	if (bars->dx[i][1] < bars->t1) {
	    continue;
	}
	if (bars->dx[i][0] > bars->t2) {
	    break;
	}
	started = stopped = 0;
	if (bars->dx[i][0] >= bars->t1) {

	    fprintf(fp, "%.3f %.10g %.10g\n", bars->dx[i][0], y0, y1);
	    started = 1;
	}
	if (bars->dx[i][1] <= bars->t2) {

	    if (!started) {

		fprintf(fp, "%.3f %.10g %.10g\n", bars->t1, y0, y1);
	    }
	    fprintf(fp, "%.3f %.10g %.10g\n", bars->dx[i][1], y0, y1);
	    fputs("e\n", fp);
	    stopped = 1;
	}
	if (started && !stopped) {

	    fprintf(fp, "%.3f %.10g %.10g\n", bars->t2, y0, y1);
	    fputs("e\n", fp);
	}
    }
}
