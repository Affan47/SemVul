rebakb_(integer *nm, integer *n, doublereal *b,
        doublereal *dl, integer *m, doublereal *z)
{

    integer b_dim1, b_offset, z_dim1, z_offset, i_1, i_2, i_3;


    static integer i, j, k;
    static doublereal x;
    static integer i1, ii;


    --dl;
    b_dim1 = *nm;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    z_dim1 = *nm;
    z_offset = z_dim1 + 1;
    z -= z_offset;


    if (*m == 0) {
        goto L200;
    }

    i_1 = *m;
    for (j = 1; j <= i_1; ++j) {

        i_2 = *n;
        for (ii = 1; ii <= i_2; ++ii) {
            i1 = *n - ii;
            i = i1 + 1;
            x = dl[i] * z[i + j * z_dim1];
            if (i == 1) {
                goto L80;
            }

            i_3 = i1;
            for (k = 1; k <= i_3; ++k) {

                x += b[i + k * b_dim1] * z[k + j * z_dim1];
            }

L80:
            z[i + j * z_dim1] = x;

        }
    }

L200:
    return 0;
}
