ColorMatch
(
    unsigned long width,
    const unsigned char *map,
    unsigned char *rgb,
    unsigned char *kplane,
    unsigned char *cplane,
    unsigned char *mplane,
    unsigned char *yplane
)
{
    static      BYTE        prev_red = 255, prev_green = 255, prev_blue = 255;
    static      BYTE        bcyan, bmagenta, byellow, bblack;

    BYTE    r;
    BYTE    g;
    BYTE    b;

    for (unsigned long i = 0; i < width; i++)
    {
        r = *rgb++;
        g = *rgb++;
        b = *rgb++;
        if(i == 0 || ( (prev_red != r) || (prev_green != g) || (prev_blue != b) ))
        {
            prev_red =   r;
            prev_green = g;
            prev_blue =  b;

            Interpolate(map, (BYTE)r, (BYTE)g,(BYTE)b, &bblack, &bcyan, &bmagenta, &byellow);
        }
        if (kplane)
            *(kplane + i) = bblack;
        if (cplane)
            *(cplane + i) = bcyan;
        if (mplane)
            *(mplane + i) = bmagenta;
        if (yplane)
            *(yplane + i) = byellow;

    }

}
