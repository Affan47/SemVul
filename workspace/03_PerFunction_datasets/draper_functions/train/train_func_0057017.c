ipstr_(doublereal *omega)
{

    integer i__1;


    static integer ip;
    static doublereal wm1;


    wm1 = *omega - 1.;

    for (ip = 6; ip <= 940; ++ip) {
        i__1 = ip - 1;
        if ((doublereal) ((real) ip) * pow_di(&wm1, &i__1) <= .5)
            return ip;
    }
    return 940;
}
