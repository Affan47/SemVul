CalcRedValPower(FIXP_DBL num,
                                FIXP_DBL denum,
                                INT*     scaling )
{
    FIXP_DBL value = FL2FXCONST_DBL(0.f);

    if (num>=FL2FXCONST_DBL(0.f)) {
      value = fDivNorm( num, denum, scaling);
    }
    else {
      value = -fDivNorm( -num, denum, scaling);
    }
    value = f2Pow(value, *scaling, scaling);
    *scaling = DFRACT_BITS-1-*scaling;

    return value;
}
