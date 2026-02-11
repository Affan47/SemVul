kmo_priv_moffat1d_fncd(const double x[], const double a[], double result[])
{

    if (a == NULL)
        result = NULL;

    double bb = (1 + pow(((x[0]-a[2])/a[3]),2));
    double aa = pow(bb, -a[4]);


    result[0] = 1;


    result[1] = aa;


    result[2] = 2*a[1]*a[4]*(x[0]-a[2])*pow(bb, -a[4]-1) / pow(a[3], 2);


    result[3] = 2*a[1]*a[4]*pow((x[0]-a[2]), 2)*pow(bb, -a[4]-1) / pow(a[3], 3);


    result[4] = -a[1]*aa*log(bb);

    return 0;
}
