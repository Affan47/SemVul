pixaGetBoxaCount(PIXA  *pixa)
{
    PROCNAME("pixaGetBoxaCount");

    if (!pixa)
        return ERROR_INT("pixa not defined", procName, 0);

    return boxaGetCount(pixa->boxa);
}
