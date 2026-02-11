GDD(Real omega) const
{
    int i, n;
    Real x = omega - omega0;
    Real GDD = 0;
    n = beta.size();
    for (i=n-1; i>0; i--) GDD = (GDD + beta[i]) * x / Real(i);
    GDD += beta[0];
    return GDD;
}
