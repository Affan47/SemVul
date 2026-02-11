form_Qy (double *y, int T)
{
    double tmp, lag1 = 0.0, lag2 = 0.0;
    int t;

    for (t=0; t<T-2; t++) {
	tmp = y[t];
	y[t] += lag2 - 2 * lag1;
	lag2 = lag1;
	lag1 = tmp;
    }

    y[T-2] = lag2 - 2 * lag1;
    y[T-1] = lag1;
}
