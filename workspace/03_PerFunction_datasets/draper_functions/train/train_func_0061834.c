WriteLine5x(byte *dest, byte *src)
{
    int x;

    for (x=0; x<SCREENWIDTH; ++x)
    {
        dest[0] = *src;
        dest[1] = *src;
        dest[2] = *src;
        dest[3] = *src;
        dest[4] = *src;
        dest += 5;
        ++src;
    }
}
