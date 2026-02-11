epslon_(doublereal *x)
{

    doublereal ret_val, d_1;


    static doublereal a, b, c, eps;


    a = 1.3333333333333333;
L10:
    b = a - 1.;
    c = b + b + b;
    eps = (d_1 = c - 1., abs(d_1));
    if (eps == 0.) {
        goto L10;
    }
    ret_val = eps * abs(*x);
    return ret_val;
}
