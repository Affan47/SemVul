regress_ls (double *x, double *y, GMT_LONG n, double *stat, int col)
{
	GMT_LONG i;
	double sum_x, sum_y, sum_x2, sum_y2, sum_xy, d, ss;
	double mean_x, mean_y, S_xx, S_xy, S_yy, y_discrepancy;

	sum_x = sum_y = sum_x2 = sum_y2 = sum_xy = y_discrepancy = 0.0;
	mean_x = mean_y = S_xx = S_xy = S_yy = ss = 0.0;
	for (i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_x2 += x[i] * x[i];
		sum_y2 += y[i] * y[i];
		sum_xy += x[i] * y[i];
		ss += (x[i] - y[i])*(x[i] - y[i]);
	}

	mean_x = sum_x / n;
	mean_y = sum_y / n;

	for (i = 0; i < n; i++) {
		S_xx += (x[i] - mean_x) * (x[i] - mean_x);
		S_yy += (y[i] - mean_y) * (y[i] - mean_y);
		S_xy += (x[i] - mean_x) * (y[i] - mean_y);
	}


	if (col != MGD77_DEPTH) {
		stat[MGD77_RLS_SLOPE] = S_xy / S_xx;
		stat[MGD77_RLS_ICEPT] = mean_y - stat[MGD77_RLS_SLOPE] * mean_x;
	}

	for (i = 0; i < n; i++) {
		d = y[i] - stat[MGD77_RLS_SLOPE] * x[i] - stat[MGD77_RLS_ICEPT];
		y_discrepancy += d*d;
	}
	stat[MGD77_RLS_STD] = sqrt (y_discrepancy / (n-1));
	stat[MGD77_RLS_SXX] = S_xx;
	stat[MGD77_RLS_CORR] = sqrt(S_xy * S_xy / (S_xx * S_yy));
	stat[MGD77_RLS_RMS] = sqrt(ss / n);
	stat[MGD77_RLS_SUMX2] = sum_x2;
}
