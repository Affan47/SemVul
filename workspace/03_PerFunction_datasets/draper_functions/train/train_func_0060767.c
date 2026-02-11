test_array_free_custom(void *_mem, void *info)
{
    unsigned char *mem;
    int *mem_used=(int *)info;
    size_t extra;


    extra=MAX(sizeof(void *),sizeof(size_t));

    if(_mem!=NULL) {
        mem=((unsigned char *)_mem)-extra;
        *mem_used-=*(size_t *)mem;
        HDfree(mem);
    }
}
