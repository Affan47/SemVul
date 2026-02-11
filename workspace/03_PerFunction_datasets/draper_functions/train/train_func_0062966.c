read_vectorram (int addr, int *x, int *y, int *c)
{
    *c = aztarac_vectorram[addr] & 0xffff;
    *x = aztarac_vectorram[addr + 0x800] & 0x03ff;
    *y = aztarac_vectorram[addr + 0x1000] & 0x03ff;
    if (*x & 0x200) *x |= 0xfffffc00;
    if (*y & 0x200) *y |= 0xfffffc00;
}
