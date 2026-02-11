FreeImage_LookupX11Color(const char *szColor, BYTE *nRed, BYTE *nGreen, BYTE *nBlue) {
    int i;


    i = FreeImage_LookupNamedColor(szColor, X11ColorMap, sizeof(X11ColorMap)/sizeof(X11ColorMap[0]));
    if (i >= 0) {
        *nRed   = X11ColorMap[i].r;
        *nGreen = X11ColorMap[i].g;
        *nBlue  = X11ColorMap[i].b;
        return TRUE;
    }


    if ( (szColor[0] == 'g' || szColor[0] == 'G') &&
         (szColor[1] == 'r' || szColor[1] == 'R') &&
         (szColor[2] == 'e' || szColor[2] == 'E' || szColor[2] == 'a' || szColor[2] == 'A' ) &&
         (szColor[3] == 'y' || szColor[3] == 'Y' ) )  {


        i = strtol(szColor+4, NULL, 10);
        *nRed   = (BYTE)(255.0/100.0 * i);
        *nGreen = *nRed;
        *nBlue  = *nRed;

        return TRUE;
    }


    *nRed   = 0;
    *nGreen = 0;
    *nBlue  = 0;

    return FALSE;
}
