dpnorm (double x, int lower_tail, double lp)
{


    if (x < 0) {
	x = -x;
	lower_tail = !lower_tail;
    }

    if (x > 10 && !lower_tail) {
	double term = 1 / x;
	double sum = term;
	double x2 = x * x;
	double i = 1;

	do {
	    term *= -i / x2;
	    sum += term;
	    i += 2;
	} while (fabs (term) > DBL_EPSILON * sum);

	return 1 / sum;
    } else {
	double d = dnorm (x, 0, 1, FALSE);
	return d / exp (lp);
    }
}
