dialnorm2progreflvl(const INT d)
{
    return ((UCHAR)FDKmax(0, FDKmin((-d + (1<<13)) >> 14, 127)));
}
