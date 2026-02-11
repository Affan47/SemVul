bakvec_(integer *nm, integer *n, doublereal *t,
        doublereal *e, integer *m, doublereal *z, integer *ierr)
{

    integer t_dim1, t_offset, z_dim1, z_offset, i_1, i_2;


    static integer i, j;


    t_dim1 = *nm;
    t_offset = t_dim1 + 1;
    t -= t_offset;
    --e;
    z_dim1 = *nm;
    z_offset = z_dim1 + 1;
    z -= z_offset;


    *ierr = 0;
    if (*m == 0) {
        goto L1001;
    }
    e[1] = 1.;
    if (*n == 1) {
        goto L1001;
    }

    i_1 = *n;
    for (i = 2; i <= i_1; ++i) {
        if (e[i] != 0.) {
            goto L80;
        }
        if (t[i + t_dim1] != 0. || t[i - 1 + t_dim1 * 3] != 0.) {
            goto L1000;
        }
        e[i] = 1.;
        goto L100;
L80:
        e[i] = e[i - 1] * e[i] / t[i - 1 + t_dim1 * 3];
L100:
        ;
    }

    i_1 = *m;
    for (j = 1; j <= i_1; ++j) {

        i_2 = *n;
        for (i = 2; i <= i_2; ++i) {
            z[i + j * z_dim1] *= e[i];

        }
    }

    goto L1001;


L1000:
    *ierr = (*n << 1) + i;
L1001:
    return 0;
}
