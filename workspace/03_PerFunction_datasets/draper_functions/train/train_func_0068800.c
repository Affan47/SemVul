_glfwSplitBPP(int bpp, int* red, int* green, int* blue)
{
    int delta;


    if (bpp == 32)
        bpp = 24;


    *red = *green = *blue = bpp / 3;
    delta = bpp - (*red * 3);
    if (delta >= 1)
        *green = *green + 1;

    if (delta == 2)
        *red = *red + 1;
}
