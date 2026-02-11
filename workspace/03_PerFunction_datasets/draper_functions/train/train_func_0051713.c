GetHPSig(void)
{
    unsigned int hpSig = 0;
    pieceT * b = &(Board[A2]);
    if(*b == WP)
    {
        hpSig |= 0x8000;
    }
    b++;
    if(*b == WP)
    {
        hpSig |= 0x4000;
    }
    b++;
    if(*b == WP)
    {
        hpSig |= 0x2000;
    }
    b++;
    if(*b == WP)
    {
        hpSig |= 0x1000;
    }
    b++;
    if(*b == WP)
    {
        hpSig |= 0x0800;
    }
    b++;
    if(*b == WP)
    {
        hpSig |= 0x0400;
    }
    b++;
    if(*b == WP)
    {
        hpSig |= 0x0200;
    }
    b++;
    if(*b == WP)
    {
        hpSig |= 0x0100;
    }
    b = &(Board[A7]);
    if(*b == BP)
    {
        hpSig |= 0x0080;
    }
    b++;
    if(*b == BP)
    {
        hpSig |= 0x0040;
    }
    b++;
    if(*b == BP)
    {
        hpSig |= 0x0020;
    }
    b++;
    if(*b == BP)
    {
        hpSig |= 0x0010;
    }
    b++;
    if(*b == BP)
    {
        hpSig |= 0x0008;
    }
    b++;
    if(*b == BP)
    {
        hpSig |= 0x0004;
    }
    b++;
    if(*b == BP)
    {
        hpSig |= 0x0002;
    }
    b++;
    if(*b == BP)
    {
        hpSig |= 0x0001;
    }
    return hpSig;
}
