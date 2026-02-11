d9lgic_(doublereal *a, doublereal *x, doublereal *alx)
{


     doublereal eps = 0.;


    doublereal ret_val;


    double log(doublereal);


    integer k;
    doublereal p, r__, s, t, fk, xma, xpa;
    extern doublereal d1mach_(integer *);
    extern  int xermsg_(const char *, const char *, const char *, integer *,
            integer *, ftnlen, ftnlen, ftnlen);


    eps = .5 * d1mach_(&c__3);

    xpa = *x + 1. - *a;
    xma = *x - 1. - *a;

    r__ = 0.;
    p = 1.;
    s = p;
    for (k = 1; k <= 300; ++k) {
        fk = (doublereal) k;
        t = fk * (*a - fk) * (r__ + 1.);
        r__ = -t / ((xma + fk * 2.) * (xpa + fk * 2.) + t);
        p = r__ * p;
        s += p;
        if (abs(p) < eps * s) {
            goto L20;
        }

    }
    xermsg_("SLATEC", "D9LGIC", "NO CONVERGENCE IN 300 TERMS OF CONTINUED FR"
            "ACTION", &c__1, &c__2, (ftnlen)6, (ftnlen)6, (ftnlen)49);

L20:
    ret_val = *a * *alx - *x + log(s / xpa);

    return ret_val;
}
