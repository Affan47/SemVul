rs_(integer *nm, integer *n, doublereal *a, doublereal *
        w, integer *matz, doublereal *z, doublereal *fv1, doublereal *fv2,
        integer *ierr)
{

    integer a_dim1, a_offset, z_dim1, z_offset;


    extern  int tred1_(integer *, integer *, doublereal *,
            doublereal *, doublereal *, doublereal *), tred2_(integer *,
            integer *, doublereal *, doublereal *, doublereal *, doublereal *)
            , tqlrat_(integer *, doublereal *, doublereal *, integer *),
            tql2_(integer *, integer *, doublereal *, doublereal *,
            doublereal *, integer *);


    --fv2;
    --fv1;
    z_dim1 = *nm;
    z_offset = z_dim1 + 1;
    z -= z_offset;
    --w;
    a_dim1 = *nm;
    a_offset = a_dim1 + 1;
    a -= a_offset;


    if (*n <= *nm) {
        goto L10;
    }
    *ierr = *n * 10;
    goto L50;

L10:
    if (*matz != 0) {
        goto L20;
    }

    tred1_(nm, n, &a[a_offset], &w[1], &fv1[1], &fv2[1]);
    tqlrat_(n, &w[1], &fv2[1], ierr);
    goto L50;

L20:
    tred2_(nm, n, &a[a_offset], &w[1], &fv1[1], &z[z_offset]);
    tql2_(nm, n, &w[1], &fv1[1], &z[z_offset], ierr);
L50:
    return 0;
}
