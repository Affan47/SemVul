pixaaAddPixa(PIXAA   *paa,
             PIXA    *pixa,
             l_int32  copyflag)
{
l_int32  n;
PIXA    *pixac;

    PROCNAME("pixaaAddPixa");

    if (!paa)
        return ERROR_INT("paa not defined", procName, 1);
    if (!pixa)
        return ERROR_INT("pixa not defined", procName, 1);
    if (copyflag != L_INSERT && copyflag != L_COPY &&
        copyflag != L_CLONE && copyflag != L_COPY_CLONE)
        return ERROR_INT("invalid copyflag", procName, 1);

    if (copyflag == L_INSERT) {
        pixac = pixa;
    } else {
        if ((pixac = pixaCopy(pixa, copyflag)) == NULL)
            return ERROR_INT("pixac not made", procName, 1);
    }

    n = pixaaGetCount(paa, NULL);
    if (n >= paa->nalloc)
        pixaaExtendArray(paa);
    paa->pixa[n] = pixac;
    paa->n++;

    return 0;
}
