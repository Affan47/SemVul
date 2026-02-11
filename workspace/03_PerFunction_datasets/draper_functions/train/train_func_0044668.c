Interpolate
(
    const uint32_t *map,
    BYTE r,
    BYTE g,
    BYTE b,
    BYTE *blackout,
    BYTE *cyanout,
    BYTE *magentaout,
    BYTE *yellowout
)
{
    static int cube_location[]  = {0, 1,  9, 10,  81,  82,  90,  91 };
    const uint32_t *start;

#ifdef  _WIN32_WCE
    long    cyan[8], magenta[8],yellow[8],black[8];
#else
    BYTE    cyan[8], magenta[8],yellow[8],black[8];
#endif
    start = (const uint32_t *)
        (((r & 0xE0) << 1) + ((r & 0xE0) >> 1) + (r >> 5) +
        ((g & 0xE0) >> 2) + (g >> 5) + (b >> 5) + map);

    uint32_t    cValue;
    for (int j = 0; j < 8; j++)
    {
        cValue = *(start + cube_location[j]);
        cyan[j]    = GetCyanValue (cValue);
        magenta[j] = GetMagentaValue (cValue);
        yellow[j]  = GetYellowValue (cValue);
        black[j]   = GetBlackValue (cValue);
    }


    BYTE diff_red   = r & 0x1f;
    BYTE diff_green = g & 0x1f;
    BYTE diff_blue  = b & 0x1f;

    *cyanout    = INTERPOLATE_CUBE(diff_red,diff_green,diff_blue, cyan, INTERPOLATE_5_BITS );
    *magentaout = INTERPOLATE_CUBE(diff_red,diff_green,diff_blue, magenta, INTERPOLATE_5_BITS );
    *yellowout  = INTERPOLATE_CUBE(diff_red,diff_green,diff_blue, yellow, INTERPOLATE_5_BITS );
    *blackout   = INTERPOLATE_CUBE(diff_red,diff_green,diff_blue, black, INTERPOLATE_5_BITS );
}
