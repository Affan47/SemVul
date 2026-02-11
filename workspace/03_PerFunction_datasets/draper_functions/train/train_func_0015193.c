find_lowest_scalefac(const FLOAT xr34)
{
    uint8_t sf_ok = 255;
    uint8_t sf = 128, delsf = 64;
    uint8_t i;
    for (i = 0; i < 8; ++i) {
        FLOAT const xfsf = ipow20[sf] * xr34;
        if (xfsf <= IXMAX_VAL) {
            sf_ok = sf;
            sf -= delsf;
        }
        else {
            sf += delsf;
        }
        delsf >>= 1;
    }
    return sf_ok;
}
