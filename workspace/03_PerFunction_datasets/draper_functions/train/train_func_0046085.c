bmfCreate(const char  *dir,
          l_int32      size)
{
L_BMF   *bmf;
PIXA  *pixa;

    PROCNAME("bmfCreate");

    if ((bmf = (L_BMF *)CALLOC(1, sizeof(L_BMF))) == NULL)
        return (L_BMF *)ERROR_PTR("bmf not made", procName, NULL);


    pixa = pixaGetFont(dir, size, &bmf->baseline1, &bmf->baseline2,
                       &bmf->baseline3);


    if (!pixa) {
        L_INFO("Generating pixa of bitmap fonts", procName);
        pixa = pixaGenerateFont(dir, size, &bmf->baseline1, &bmf->baseline2,
                                &bmf->baseline3);
        if (!pixa) {
            bmfDestroy(&bmf);
            return (L_BMF *)ERROR_PTR("font pixa not made", procName, NULL);
        }
    }

    bmf->pixa = pixa;
    bmf->size = size;
    bmf->directory = stringNew(dir);
    bmfMakeAsciiTables(bmf);
    return bmf;
}
