up_ll(LIKELIHOOD * pt1,
		  int M, double alpha, LIKELIHOOD * pt2
    )
{
    static int m;
    static double sum, max, cprob[256];

    if (alpha != 1.0) {
	max = pt1[0];
	for (m = 1; m < M; m++)
	    if (pt1[m] > max)
		max = pt1[m];

	sum = 0;
	for (m = 0; m < M; m++) {
	    cprob[m] = exp(pt1[m] - max);
	    sum += cprob[m];
	}

	sum = ((1 - alpha) * sum) / M;

	for (m = 0; m < M; m++)
	    pt2[m] += log(sum + alpha * cprob[m]) + max;
    }
    else {
	for (m = 0; m < M; m++)
	    pt2[m] += pt1[m];
    }
}
