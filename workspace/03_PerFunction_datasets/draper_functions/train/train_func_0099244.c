FcSortCompare (const void *aa, const void *ab)
{
    FcSortNode  *a = *(FcSortNode **) aa;
    FcSortNode  *b = *(FcSortNode **) ab;
    double	*as = &a->score[0];
    double	*bs = &b->score[0];
    double	ad = 0, bd = 0;
    int         i;

    i = a->n;
    while (i-- && (ad = *as++) == (bd = *bs++))
        ;
    return ad < bd ? -1 : ad > bd ? 1 : 0;
}
