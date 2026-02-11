I_Scale2x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp, *screenp2;
    int x, y;
    int multi_pitch;

    multi_pitch = dest_pitch * 2;
    bufp = src_buffer + y1 * SCREENWIDTH + x1;
    screenp = (byte *) dest_buffer + (y1 * dest_pitch + x1) * 2;
    screenp2 = screenp + dest_pitch;

    for (y=y1; y<y2; ++y)
    {
        byte *sp, *sp2, *bp;
        sp = screenp;
        sp2 = screenp2;
        bp = bufp;

        for (x=x1; x<x2; ++x)
        {
            *sp++ = *bp;  *sp++ = *bp;
            *sp2++ = *bp; *sp2++ = *bp;
            ++bp;
        }
        screenp += multi_pitch;
        screenp2 += multi_pitch;
        bufp += SCREENWIDTH;
    }

    return true;
}
