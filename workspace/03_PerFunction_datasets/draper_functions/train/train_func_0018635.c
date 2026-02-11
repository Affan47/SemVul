p96depth (int depth)
{
    uae_u32 f = currprefs.picasso96_modeflags;
    int ok = 0;

    if (depth == 8 && (f & RGBFF_CLUT))
        ok = 1;
    if (depth == 15 && (f & (RGBFF_R5G5B5PC | RGBFF_R5G5B5 | RGBFF_B5G5R5PC)))
        ok = 2;
    if (depth == 16 && (f & (RGBFF_R5G6B5PC | RGBFF_R5G6B5 | RGBFF_B5G6R5PC)))
        ok = 2;
    if (depth == 24 && (f & (RGBFF_R8G8B8 | RGBFF_B8G8R8)))
        ok = 3;
    if (depth == 32 && (f & (RGBFF_A8R8G8B8 | RGBFF_A8B8G8R8 | RGBFF_R8G8B8A8 | RGBFF_B8G8R8A8)))
        ok = 4;
    return ok;
}
