exfill(void (*fill) (PLINT, PLFLT *, PLFLT *),
       PLINT (*defined) (PLFLT, PLFLT),
       int n, PLFLT *x, PLFLT *y)
{
    if (defined == NULL)

        (*fill) (n, x, y);

    else {
        PLFLT xx[16];
	PLFLT yy[16];
	PLFLT xb, yb;
	PLINT count = 0;
	PLINT is_inside = defined (x[n-1], y[n-1]);
	PLINT i;

        for (i = 0; i < n; i++) {

	    if (defined(x[i], y[i])) {
	        if (!is_inside) {
		    if (i > 0)
		        bisect (defined, 10,
				x[i], y[i], x[i-1], y[i-1], &xb, &yb);
		    else
		        bisect (defined, 10,
				x[i], y[i], x[n-1], y[n-1], &xb, &yb);
		    xx[count] = xb;
		    yy[count++] = yb;
		}
		xx[count] = x[i];
		yy[count++] = y[i];
		is_inside = 1;
	    }
	    else {
	        if (is_inside) {
		    if (i > 0)
		        bisect (defined, 10,
				x[i-1], y[i-1], x[i], y[i], &xb, &yb);
		    else
		        bisect (defined, 10,
				x[n-1], y[n-1], x[i], y[i], &xb, &yb);
		    xx[count] = xb;
		    yy[count++] = yb;
		    is_inside = 0;
		}
	    }
	}

	if (count)
  	    (*fill) (count, xx, yy);
    }
}
