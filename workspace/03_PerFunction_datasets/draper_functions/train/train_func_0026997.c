GC_generic_malloc_inner_ignore_off_page(lb, k)
register size_t lb;
register int k;
{
    register word lw;
    ptr_t op;

    if (lb <= HBLKSIZE)
        return(GC_generic_malloc_inner((word)lb, k));
    lw = ROUNDED_UP_WORDS(lb);
    op = (ptr_t)GC_alloc_large_and_clear(lw, k, IGNORE_OFF_PAGE);
    GC_words_allocd += lw;
    return op;
}
