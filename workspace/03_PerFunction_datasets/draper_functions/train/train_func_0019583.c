dcopy_(integer    *n,
			    doublereal *dx,
			    integer    *incx,
			    doublereal *dy,
			    integer    *incy)
{

    integer i__1;


    static integer i, m, ix, iy, mp1;


    --dy;
    --dx;


    if (*n <= 0) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }


    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
	dy[iy] = dx[ix];
	ix += *incx;
	iy += *incy;

    }
    return 0;


L20:
    m = *n % 7;
    if (m == 0) {
	goto L40;
    }
    i__1 = m;
    for (i = 1; i <= i__1; ++i) {
	dy[i] = dx[i];

    }
    if (*n < 7) {
	return 0;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i = mp1; i <= i__1; i += 7) {
	dy[i] = dx[i];
	dy[i + 1] = dx[i + 1];
	dy[i + 2] = dx[i + 2];
	dy[i + 3] = dx[i + 3];
	dy[i + 4] = dx[i + 4];
	dy[i + 5] = dx[i + 5];
	dy[i + 6] = dx[i + 6];

    }
    return 0;
}
