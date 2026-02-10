sklearn_lgamma(double x)
{


    static const double c[8] =
    {
         1.0/12.0,
        -1.0/360.0,
         1.0/1260.0,
        -1.0/1680.0,
         1.0/1188.0,
        -691.0/360360.0,
         1.0/156.0,
        -3617.0/122400.0
    };

    double z, sum;
    int i;

    if (x < 12.0)
        return log(fabs(sklearn_gamma(x)));

    z = 1.0 / (x * x);
    sum = c[7];
    for (i=6; i >= 0; i--) {
        sum *= z;
        sum += c[i];
    }

    return (x - 0.5) * log(x) - x + HALF_LOG2_PI + sum / x;
}
