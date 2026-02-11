av_realloc(void *ptr, unsigned int size)
{
#if CONFIG_MEMALIGN_HACK
    int diff;
#endif


    if(size > (INT_MAX-16) )
        return NULL;

#if CONFIG_MEMALIGN_HACK

    if(!ptr) return av_malloc(size);
    diff= ((char*)ptr)[-1];
    ptr= realloc((char*)ptr - diff, size + diff);
    if(ptr) ptr = (char*)ptr + diff;
    return ptr;
#else
    return realloc(ptr, size);
#endif
}
