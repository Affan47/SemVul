pixaAddBox(PIXA    *pixa,
           BOX     *box,
           l_int32  copyflag)
{
    PROCNAME("pixaAddBox");

    if (!pixa)
        return ERROR_INT("pixa not defined", procName, 1);
    if (!box)
        return ERROR_INT("box not defined", procName, 1);
    if (copyflag != L_INSERT && copyflag != L_COPY && copyflag != L_CLONE)
        return ERROR_INT("invalid copyflag", procName, 1);

    boxaAddBox(pixa->boxa, box, copyflag);
    return 0;
}
