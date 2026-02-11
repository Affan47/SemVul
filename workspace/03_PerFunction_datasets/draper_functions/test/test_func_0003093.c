_gammcf(double a, double x, double logGamma) const {

    double an,b,c,d,del,h;
    int i;

    b = x + 1.0 -a;
    c = 1.0/FPMIN;
    d = 1.0/b;
    h = d;
    for (i=1;i<ITMAX;i++) {
        an = -i*(i-a);
        b+=2.0;
        d=an*d+b;
        if (fabs(d) < FPMIN) d = FPMIN;
        c = b+an/c;
        if (fabs(c) < FPMIN) c = FPMIN;
        d = 1.0/d;
        del=d*c;
        h *= del;
        if (fabs(del-1.0) < EPS) return exp(-x+a*log(x)-logGamma)*h;
    }
    assert(0);
    return 0;
}
