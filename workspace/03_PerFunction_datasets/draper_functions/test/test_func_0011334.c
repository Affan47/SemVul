pickTileSeparateCase(TIFFRGBAImage* img)
{
    tileSeparateRoutine put = 0;

    if (buildMap(img)) {
        switch (img->photometric) {
        case PHOTOMETRIC_RGB:
            switch (img->bitspersample) {
            case 8:
                if (!img->Map) {
                    if (img->alpha == EXTRASAMPLE_ASSOCALPHA)
                        put = putRGBAAseparate8bittile;
                    else if (img->alpha == EXTRASAMPLE_UNASSALPHA)
                        put = putRGBUAseparate8bittile;
                    else
                        put = putRGBseparate8bittile;
                } else
                    put = putRGBseparate8bitMaptile;
                break;
            case 16:
                put = putRGBseparate16bittile;
                if (!img->Map) {
                    if (img->alpha == EXTRASAMPLE_ASSOCALPHA)
                        put = putRGBAAseparate16bittile;
                    else if (img->alpha == EXTRASAMPLE_UNASSALPHA)
                        put = putRGBUAseparate16bittile;
                }
                break;
            }
            break;
        }
    }
    return ((img->put.separate = put) != 0);
}
