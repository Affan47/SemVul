andoyer_lambert_thomas (double lat1, double lon1, double lat2, double lon2) {

    const double RM = 6367449.14582342;

    double f = 0.5 * (lat2 + lat1) * DEG_RADS;
    double g = 0.5 * (lat2 - lat1) * DEG_RADS;
    double l = 0.5 * (lon2 - lon1) * DEG_RADS;

    double sf = sin(f), sg = sin(g), sl = sin(l);
    double s2f = sf * sf, s2g = sg * sg, s2l = sl * sl;
    double c2f = 1. - s2f, c2g = 1. - s2g, c2l = 1. - s2l;

    double s2 = s2g * c2l + c2f * s2l;
    double c2 = c2g * c2l + s2f * s2l;

    double s, c, omega, rr, aa, bb, pp, qq, d2, qp, eps1, eps2;

    if (s2 == 0.) return 0.;
    if (c2 == 0.) return M_PI * RM / KILOMETER_RHO * 0.001;

    s = sqrt(s2), c = sqrt(c2);
    omega = atan2(s, c);
    rr = s * c;
    aa = s2g * c2f / s2 + s2f * c2g / c2;
    bb = s2g * c2f / s2 - s2f * c2g / c2;
    pp = rr / omega;
    qq = omega / rr;
    d2 = s2 - c2;
    qp = qq + 6. * pp;
    eps1 = 0.5 * F * (-aa - 3. * bb * pp);
    eps2 = 0.25 * F * F * ((-qp * bb + (-3.75 + d2 * (qq + 3.75 * pp)) *
            aa + 4. - d2 * qq) * aa - (7.5 * d2 * bb * pp - qp) * bb);

    double d = 2. * omega * A * (1. + eps1 + eps2);
    return d / KILOMETER_RHO * 0.001;
}
