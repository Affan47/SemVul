plctest(PLFLT *x, PLFLT level)
{
    int i, j;
    double t[4], sorted[4], temp;

    (void) level;

    sorted[0] = t[0] = X(1,1);
    sorted[1] = t[1] = X(2,2);
    sorted[2] = t[2] = X(1,2);
    sorted[3] = t[3] = X(2,1);

    for (j = 1; j < 4; j++) {
	temp = sorted[j];
	i = j - 1;
	while (i >= 0 && sorted[i] > temp) {
	    sorted[i+1] = sorted[i];
	    i--;
	}
	sorted[i+1] = temp;
    }


    temp = int_val * ceil(sorted[0]/int_val);
    if (temp < sorted[1]) {

	for (i = 0; i < 4; i++) {
	    if (t[i] < temp) return i/2;
	}
    }


    temp = int_val * floor(sorted[3]/int_val);
    if (temp > sorted[2]) {

	for (i = 0; i < 4; i++) {
	    if (t[i] > temp) return i/2;
	}
    }

    return POSITIVE_SLOPE;
}
