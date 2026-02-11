c_skew(DCELL * result, DCELL * values, int n, const void *closure)
{
    DCELL sum, ave, sumsq, sumcb, sdev;
    int count;
    int i;

    sum = 0.0;
    count = 0;

    for (i = 0; i < n; i++) {
	if (G_is_d_null_value(&values[i]))
	    continue;

	sum += values[i];
	count++;
    }

    if (count == 0) {
	G_set_d_null_value(result, 1);
	return;
    }

    ave = sum / count;

    sumsq = 0;

    for (i = 0; i < n; i++) {
	DCELL d;

	if (G_is_d_null_value(&values[i]))
	    continue;

	d = values[i] - ave;
	sumsq += d * d;
	sumcb += d * d * d;
    }

    sdev = sqrt(sumsq / count);

    *result = sumcb / (count * sdev * sdev * sdev);
}
