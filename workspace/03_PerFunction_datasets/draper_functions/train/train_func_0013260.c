numaGetNonzeroRange(NUMA      *na,
                    l_float32  eps,
                    l_int32   *pfirst,
                    l_int32   *plast)
{
l_int32    n, i, found;
l_float32  val;

    PROCNAME("numaGetNonzeroRange");

    if (!na)
        return ERROR_INT("na not defined", procName, 1);
    if (!pfirst || !plast)
        return ERROR_INT("pfirst and plast not both defined", procName, 1);
    n = numaGetCount(na);
    found = FALSE;
    for (i = 0; i < n; i++) {
        numaGetFValue(na, i, &val);
        if (val > eps) {
            found = TRUE;
            break;
        }
    }
    if (!found) {
        *pfirst = n - 1;
        *plast = 0;
        return 1;
    }

    *pfirst = i;
    for (i = n - 1; i >= 0; i--) {
        numaGetFValue(na, i, &val);
        if (val > eps)
            break;
    }
    *plast = i;
    return 0;
}
