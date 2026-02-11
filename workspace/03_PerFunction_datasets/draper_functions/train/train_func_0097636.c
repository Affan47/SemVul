get24(const unsigned char* pSrc)
    {
        const int x = pSrc[0] | pSrc[1] << 8 | pSrc[2] << 16;
        return x & 0x800000 ? x - 0x1000000 : x;
    }
