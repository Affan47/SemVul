initBlockAllocator(void)
{
    nat i;
    for (i=0; i < MAX_FREE_LIST; i++) {
        free_list[i] = NULL;
    }
    free_mblock_list = NULL;
    n_alloc_blocks = 0;
    hw_alloc_blocks = 0;
}
