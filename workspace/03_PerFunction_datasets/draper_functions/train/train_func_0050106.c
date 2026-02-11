get_pixel(int *pDst, const uint8 *pSrc, bool luma_only, int num_comps)
{
    int r, g, b;
    if (num_comps == 1) {
        r = g = b = pSrc[0];
    } else if (luma_only) {
        const int YR = 19595, YG = 38470, YB = 7471;
        r = g = b = (pSrc[0] * YR + pSrc[1] * YG + pSrc[2] * YB + 32768) / 65536;
    } else {
        r = pSrc[0]; g = pSrc[1]; b = pSrc[2];
    }
    pDst[0] = r; pDst[1] = g; pDst[2] = b;
}
