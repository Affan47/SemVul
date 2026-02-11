bv_hash(BitVector *bv)
{
    unsigned long hash = 0;
    const f_u32 empty_word = bv->extends_as_ones ? 0xFFFFFFFF : 0;
    int i;
    for (i = (bv->size >> 5); i >= 0; i--) {
        const f_u32 word = bv->bits[i];
        if (word != empty_word) {
            hash = (hash << 1) ^ word;
        }
    }
    hash = (hash << 1) | bv->extends_as_ones;
    return hash;
}
