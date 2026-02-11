fip (unsigned per, double eint, double pv, double pmt, double fv, unsigned bep)
{
    double AA = _A (eint, per);
    double CC = _C (eint, pmt, bep);
    double D = (AA + 1.0) / (1.0 + eint);
    g_return_val_if_fail(CC != 0.0, 0.0);
    return (double) per * (pv + CC) * D - (AA * CC) / eint;
}
