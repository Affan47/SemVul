locatePtRadially(l_int32     xr,
                 l_int32     yr,
                 l_float64   dist,
                 l_float64   radang,
                 l_float64  *px,
                 l_float64  *py)
{
    PROCNAME("locatePtRadially");

    if (!px || !py)
        return ERROR_INT("&x and &y not both defined", procName, 1);

    *px = xr + dist * cos(radang);
    *py = yr + dist * sin(radang);
    return 0;
}
