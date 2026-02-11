distanceDistribution(const vector<double> &d1,
                                          const vector<double> &d2,
                                          bool symmetrised)
{
    int sz = d1.size();

    double d = 0;
    double small = 1e-20;

    for (int i = 0; i < sz; ++i) {
        d += d1[i] * log10((d1[i] + small) / (d2[i] + small));
    }

    if (symmetrised) {
        d += distanceDistribution(d2, d1, false);
    }

    return d;
}
