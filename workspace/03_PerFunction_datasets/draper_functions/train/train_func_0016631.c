unscal_(integer *n, integer *ia, integer *ja, doublereal *a, doublereal *rhs, doublereal *u, doublereal *d)
{

    static doublereal di;
    static integer ii, jj, is, jajj, ibgn, iend, jjpi, inew;


    for (ii = 0; ii < *n; ++ii) {
        di = a[ii];
        u[ii] /= di;
        rhs[ii] *= di;
        d[ii] = di;
    }


    for (ii = 0; ii < *n; ++ii) {
        ibgn = ia[ii] - 1;
        iend = ia[ii + 1] - 1;
        di = d[ii];
        for (jj = ibgn; jj < iend; ++jj) {
            jajj = ja[jj];
            a[jj] *= di * d[jajj-1];
        }
    }


    for (ii = 0; ii < *n; ++ii) {
        ibgn = ia[ii] - 1;
        iend = ia[ii + 1] - 1;
        is = *n - ii - 1;
        inew = ibgn - is - 1;
        a[inew] = d[ii] * d[ii];
        ja[inew] = ii + 1;
        if (is != 0)
            for (jj = ibgn; jj < iend; ++jj) {
                jjpi = jj - is;
                a[jjpi] = a[jj];
                ja[jjpi] = ja[jj];
            }
        ia[ii] = inew + 1;
    }

    return 0;
}
