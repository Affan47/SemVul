libapetag_print_mem_cnt (apetag *mem_cnt)
{
    int n;
    struct tag **mTag;

    mTag = (mem_cnt->tag);
    for (n = 0; (mem_cnt->countTag) > n; n++) {
        if ( (mTag[n]->flags & ~ITEM_TEXT) == 0 ||
            (mTag[n]->flags & ~ITEM_LINK) == 0 ) {
        printf (">apetaglib>PRINT>>F=%li SN=%li SV=%li N[%s] V[%s]\n",
            mTag[n]->flags,
            (long) mTag[n]->sizeName, (long) mTag[n]->sizeValue,
            mTag[n]->name, mTag[n]->value);
        } else {
        printf (">apetaglib>PRINT>>F=%li SN=%li SV=%li N[%s] V=BINARY\n",
            mTag[n]->flags,
            (long) mTag[n]->sizeName, (long) mTag[n]->sizeValue,
            mTag[n]->name);
        }
    }

    return;
}
