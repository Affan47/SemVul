sinfo_ipow(double x, int p)
{
    double r, recip ;


    switch (p) {
        case 0:
        return 1.00 ;

        case 1:
        return x ;

        case 2:
        return x*x ;

        case 3:
        return x*x*x ;

        case -1:
        return 1.00 / x ;

        case -2:
        return (1.00 / x) * (1.00 / x) ;
    }
    if (p>0) {
        r = x ;
        while (--p) r *= x ;
    } else {
        r = recip = 1.00 / x ;
        while (++p) r *= recip ;
    }
    return r;
}
