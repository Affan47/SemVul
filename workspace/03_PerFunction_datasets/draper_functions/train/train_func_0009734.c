jisx0201_k_decoder(const unsigned char *data)
{
    ucs4_t u;
    JISX0201_K_DECODE(*data ^ 0x80, u)
    else return MAP_UNMAPPABLE;
    return u;
}
