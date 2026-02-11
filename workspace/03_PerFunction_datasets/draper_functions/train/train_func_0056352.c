pixacompGetBoxa(PIXAC   *pixac,
                l_int32  accesstype)
{
    PROCNAME("pixacompGetBoxa");

    if (!pixac)
        return (BOXA *)ERROR_PTR("pixac not defined", procName, NULL);
    if (!pixac->boxa)
        return (BOXA *)ERROR_PTR("boxa not defined", procName, NULL);
    if (accesstype != L_COPY && accesstype != L_CLONE &&
        accesstype != L_COPY_CLONE)
        return (BOXA *)ERROR_PTR("invalid accesstype", procName, NULL);

    return boxaCopy(pixac->boxa, accesstype);
}
