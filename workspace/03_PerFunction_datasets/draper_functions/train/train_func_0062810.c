GDALColorReliefFindNamedColor(const char *pszColorName, int *pnR, int *pnG, int *pnB)
{
    unsigned int i;

    *pnR = *pnG = *pnB = 0;
    for (i = 0; i < sizeof(namedColors) / sizeof(namedColors[0]); i++)
    {
        if (EQUAL(pszColorName, namedColors[i].name))
        {
            *pnR = (int)(255. * namedColors[i].r);
            *pnG = (int)(255. * namedColors[i].g);
            *pnB = (int)(255. * namedColors[i].b);
            return TRUE;
        }
    }
    return FALSE;
}
