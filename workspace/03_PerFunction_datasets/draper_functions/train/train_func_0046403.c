matupd_(int n, int m, double *ws, double *wy, double *sy,
		   double *ss, double *d, double *r, int *itail,
		   int iupdat, int *col, int *head, double *theta,
		   double rr, double dr, double stp, double dtd)
{
    int ws_offset, wy_offset, sy_offset, ss_offset, i1, i2;
    int j, pointr;

    --r;
    --d;
    ss_offset = 1 + m;
    ss -= ss_offset;
    sy_offset = 1 + m;
    sy -= sy_offset;
    wy_offset = 1 + n;
    wy -= wy_offset;
    ws_offset = 1 + n;
    ws -= ws_offset;

    if (iupdat <= m) {
	*col = iupdat;
	*itail = (*head + iupdat - 2) % m + 1;
    } else {
	*itail = *itail % m + 1;
	*head = *head % m + 1;
    }

    dcopy_(n, &d[1], &ws[*itail * n + 1]);
    dcopy_(n, &r[1], &wy[*itail * n + 1]);
    *theta = rr / dr;

    if (iupdat > m) {
	i1 = *col - 1;
	for (j = 1; j <= i1; ++j) {
	    dcopy_(j, &ss[(j + 1) * m + 2], &ss[j * m + 1]);
	    i2 = *col - j;
	    dcopy_(i2, &sy[j + 1 + (j + 1) * m], &sy[j + j * m]);
	}
    }

    pointr = *head;
    i1 = *col - 1;

    for (j = 1; j <= i1; ++j) {
	sy[*col + j * m] = ddot_(n, &d[1], &wy[pointr * n + 1]);
	ss[j + *col * m] = ddot_(n, &ws[pointr * n + 1], &d[1]);
	pointr = pointr % m + 1;
    }

    if (stp == 1.) {
	ss[*col + *col * m] = dtd;
    } else {
	ss[*col + *col * m] = stp * stp * dtd;
    }
    sy[*col + *col * m] = dr;

    return 0;
}
