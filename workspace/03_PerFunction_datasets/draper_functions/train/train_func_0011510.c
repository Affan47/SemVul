plfit_kolmogorov(double z) {
    const double fj[4] = { -2, -8, -18, -32 };
    const double w = 2.50662827;
    const double c1 = -1.2337005501361697;
    const double c2 = -11.103304951225528;
    const double c3 = -30.842513753404244;

    double u = fabs(z);
    double v;

    if (u < 0.2)
        return 1;

    if (u < 0.755) {
        v = 1.0 / (u*u);
        return 1 - w * (exp(c1*v) + exp(c2*v) + exp(c3*v)) / u;
    }

    if (u < 6.8116) {
        double r[4] = { 0, 0, 0, 0 };
        long int maxj = (long int)(3.0 / u + 0.5);
        long int j;

        if (maxj < 1)
            maxj = 1;

        v = u*u;
        for (j = 0; j < maxj; j++) {
            r[j] = exp(fj[j] * v);
        }

        return 2*(r[0] - r[1] + r[2] - r[3]);
    }

    return 0;
}
