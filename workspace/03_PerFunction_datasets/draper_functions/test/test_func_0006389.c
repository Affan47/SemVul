G3d_compareDoubles(double *d1, int p1, double *d2, int p2)
{
    unsigned char *c1, *c2;
    double xdrd1, xdrd2;

    if (G3d_isNullValueNum(d1, DCELL_TYPE))
	return G3d_isNullValueNum(d2, DCELL_TYPE);

    G3d_double2xdrDouble(d1, &xdrd1);
    G3d_double2xdrDouble(d2, &xdrd2);

    c1 = (unsigned char *)&xdrd1;
    c2 = (unsigned char *)&xdrd2;


    if ((p1 != -1) && (p1 < 52) && ((p1 < p2) || (p2 == -1)))
	G3d_truncDouble(&xdrd2, p1);
    if ((p2 != -1) && (p2 < 52) && ((p2 < p1) || (p1 == -1)))
	G3d_truncDouble(&xdrd1, p2);


    return (*c1 == *c2) && (*(c1 + 1) == *(c2 + 1)) &&
	(*(c1 + 2) == *(c2 + 2))
	&& (*(c1 + 3) == *(c2 + 3)) && (*(c1 + 4) == *(c2 + 4))
	&& (*(c1 + 5) == *(c2 + 5)) && (*(c1 + 6) == *(c2 + 6))
	&& (*(c1 + 7) == *(c2 + 7));
}
