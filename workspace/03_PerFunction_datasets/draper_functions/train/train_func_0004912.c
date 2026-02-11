diveasy(divisor, uflag)
value_t divisor;
bool_pt uflag;
{
    bool_t sign;

    sign = FALSE;
    if (divisor < 0 && !(bool_t) uflag)
    {
	sign = TRUE;
	divisor = -divisor;
    }
    if (bitcount((uvalue_t) divisor) > 1)
	return FALSE;
    if (divisor == 0)
	clr(DREG);
    else
    {
	if (sign)
	    negDreg();
	srconst((value_t) highbit((uvalue_t) divisor), uflag);
    }
    return TRUE;
}
