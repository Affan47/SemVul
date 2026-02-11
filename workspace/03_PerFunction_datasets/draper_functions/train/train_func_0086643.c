spline_solve(int n, gdouble x[], gdouble y[], gdouble y2[])
{
    gdouble p, sig, *u;
    gint i, k;

    u = g_new(gdouble, (n - 1));

    y2[0] = u[0] = 0.0;

    for (i = 1; i < n - 1; ++i) {
        sig = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
        p = sig * y2[i - 1] + 2.0;
        y2[i] = (sig - 1.0) / p;
        u[i] = ((y[i + 1] - y[i])
          / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1]));
        u[i] = (6.0 * u[i] / (x[i + 1] - x[i - 1]) - sig * u[i - 1]) / p;
    }

    y2[n - 1] = 0.0;
    for (k = n - 2; k >= 0; --k)
        y2[k] = y2[k] * y2[k + 1] + u[k];

    g_free(u);
}
