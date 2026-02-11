ShadeLine(int x, int y, int height, int shade)
{
    byte *dest;
    byte *shades;

    shades = colormaps + 9 * 256 + shade * 2 * 256;
    dest = I_VideoBuffer + y * SCREENWIDTH + x;
    while (height--)
    {
        *(dest) = *(shades + *dest);
        dest += SCREENWIDTH;
    }
}
