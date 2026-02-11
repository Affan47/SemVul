pythag_(doublereal *a, doublereal *b)
{

    doublereal ret_val, d_1, d_2, d_3;


    static doublereal p, r, s, t, u;


    d_1 = abs(*a), d_2 = abs(*b);
    p = max(d_1,d_2);
    if (p == 0.) {
        goto L20;
    }

    d_2 = abs(*a), d_3 = abs(*b);

    d_1 = min(d_2,d_3) / p;
    r = d_1 * d_1;
L10:
    t = r + 4.;
    if (t == 4.) {
        goto L20;
    }
    s = r / t;
    u = s * 2. + 1.;
    p = u * p;

    d_1 = s / u;
    r = d_1 * d_1 * r;
    goto L10;
L20:
    ret_val = p;
    return ret_val;
}
