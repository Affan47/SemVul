castSigned(uinteger_t mask)
{


    uinteger_t halfChunkMask = mask >> 1;
    uinteger_t minHalfChunk = imin.value & ~halfChunkMask;
    uinteger_t maxHalfChunk = imax.value & ~halfChunkMask;
    int minHalfChunkNegativity = imin.negative;
    int maxHalfChunkNegativity = imax.negative;
    if (minHalfChunk & mask)
    {
        minHalfChunk += halfChunkMask+1;
        if (minHalfChunk == 0)
            -- minHalfChunkNegativity;
    }
    if (maxHalfChunk & mask)
    {
        maxHalfChunk += halfChunkMask+1;
        if (maxHalfChunk == 0)
            -- maxHalfChunkNegativity;
    }
    if (minHalfChunk == maxHalfChunk && minHalfChunkNegativity == maxHalfChunkNegativity)
    {
        imin.value &= mask;
        imax.value &= mask;

        imin.negative = imin.value & ~halfChunkMask;
        imax.negative = imax.value & ~halfChunkMask;
        halfChunkMask += 1;
        imin.value = (imin.value ^ halfChunkMask) - halfChunkMask;
        imax.value = (imax.value ^ halfChunkMask) - halfChunkMask;
    }
    else
    {
        imin = SignExtendedNumber(~halfChunkMask, true);
        imax = SignExtendedNumber(halfChunkMask, false);
    }
    return *this;
}
