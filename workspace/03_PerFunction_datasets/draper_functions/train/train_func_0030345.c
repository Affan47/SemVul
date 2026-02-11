getFoldedNormValue(UNewTrie *trie, UChar32 start, int32_t offset) {
    uint32_t value, leadNorm32=0;
    UChar32 limit;
    UBool inBlockZero;

    limit=start+0x400;
    while(start<limit) {
        value=utrie_get32(trie, start, &inBlockZero);
        if(inBlockZero) {
            start+=UTRIE_DATA_BLOCK_LENGTH;
        } else {
            if(value!=0) {
                leadNorm32|=value;
            }
            ++start;
        }
    }


    if(leadNorm32&_NORM_CC_MASK) {
        leadNorm32|=_NORM_CC_MASK;
    }


    leadNorm32&=~((uint32_t)0xffffffff<<_NORM_EXTRA_SHIFT);

    if(leadNorm32==0) {

        return 0;
    }


    leadNorm32|=(
        (uint32_t)_NORM_EXTRA_INDEX_TOP+
        (uint32_t)((offset-UTRIE_BMP_INDEX_LENGTH)>>UTRIE_SURROGATE_BLOCK_BITS)
    )<<_NORM_EXTRA_SHIFT;

    return leadNorm32;
}
