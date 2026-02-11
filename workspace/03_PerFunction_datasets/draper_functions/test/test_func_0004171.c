dewarpaCreate(l_int32  nptrs,
              l_int32  sampling,
              l_int32  redfactor,
              l_int32  minlines,
              l_int32  maxdist)
{
L_DEWARPA  *dewa;

    PROCNAME("dewarpaCreate");

    if (nptrs <= 0)
        nptrs = INITIAL_PTR_ARRAYSIZE;
    if (nptrs > MAX_PTR_ARRAYSIZE)
        return (L_DEWARPA *)ERROR_PTR("too many pages", procName, NULL);
    if (redfactor != 1 && redfactor != 2)
        return (L_DEWARPA *)ERROR_PTR("redfactor not in {1,2}",
                                      procName, NULL);
    if (sampling == 0) {
         sampling = DEFAULT_ARRAY_SAMPLING;
    } else if (sampling < MIN_ARRAY_SAMPLING) {
         L_WARNING("sampling too small; setting to %d\n", procName,
                   MIN_ARRAY_SAMPLING);
         sampling = MIN_ARRAY_SAMPLING;
    }
    if (minlines == 0) {
        minlines = DEFAULT_MIN_LINES;
    } else if (minlines < MIN_MIN_LINES) {
        L_WARNING("minlines too small; setting to %d\n", procName,
                  MIN_MIN_LINES);
        minlines = DEFAULT_MIN_LINES;
    }
    if (maxdist < 0)
         maxdist = DEFAULT_MAX_REF_DIST;

    if ((dewa = (L_DEWARPA *)CALLOC(1, sizeof(L_DEWARPA))) == NULL)
        return (L_DEWARPA *)ERROR_PTR("dewa not made", procName, NULL);
    if ((dewa->dewarp =
         (L_DEWARP **)CALLOC(nptrs, sizeof(L_DEWARPA *))) == NULL)
        return (L_DEWARPA *)ERROR_PTR("dewarp ptrs not made", procName, NULL);
    if ((dewa->dewarpcache =
        (L_DEWARP **)CALLOC(nptrs, sizeof(L_DEWARPA *))) == NULL)
        return (L_DEWARPA *)ERROR_PTR("dewarpcache ptrs not made",
                                      procName, NULL);
    dewa->nalloc = nptrs;
    dewa->sampling = sampling;
    dewa->redfactor = redfactor;
    dewa->minlines = minlines;
    dewa->maxdist = maxdist;
    dewa->max_linecurv = DEFAULT_MAX_LINECURV;
    dewa->min_diff_linecurv = DEFAULT_MIN_DIFF_LINECURV;
    dewa->max_diff_linecurv = DEFAULT_MAX_DIFF_LINECURV;
    dewa->max_edgeslope = DEFAULT_MAX_EDGESLOPE;
    dewa->max_edgecurv = DEFAULT_MAX_EDGECURV;
    dewa->max_diff_edgecurv = DEFAULT_MAX_DIFF_EDGECURV;

    return dewa;
}
