gnc_numeric_mul_with_error(gnc_numeric a, gnc_numeric b,
                           gint64 denom, gint how,
                           gnc_numeric * error)
{
    gnc_numeric prod  = gnc_numeric_mul(a, b, denom, how);
    gnc_numeric exact = gnc_numeric_mul(a, b, GNC_DENOM_AUTO,
                                        GNC_HOW_DENOM_REDUCE);
    gnc_numeric err   = gnc_numeric_sub(prod, exact, GNC_DENOM_AUTO,
                                        GNC_HOW_DENOM_REDUCE);
    if (error)
    {
        *error = err;
    }
    return prod;
}
