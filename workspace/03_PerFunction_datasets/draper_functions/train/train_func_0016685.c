csroot_(doublereal *xr, doublereal *xi, doublereal *yr,
        doublereal *yi)
{

    double sqrt(doublereal);


    static doublereal s, ti, tr;
    extern doublereal pythag_(doublereal *, doublereal *);


    tr = *xr;
    ti = *xi;
    s = sqrt((pythag_(&tr, &ti) + abs(tr)) * .5);
    if (tr >= 0.) {
        *yr = s;
    }
    if (ti < 0.) {
        s = -s;
    }
    if (tr <= 0.) {
        *yi = s;
    }
    if (tr < 0.) {
        *yr = ti / *yi * .5;
    }
    if (tr > 0.) {
        *yi = ti / *yr * .5;
    }
    return 0;
}
